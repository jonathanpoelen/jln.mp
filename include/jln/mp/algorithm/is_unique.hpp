// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class Cmp = same<>, class C = identity>
  struct is_unique_if
#ifdef JLN_MP_DOXYGENATING
  {
    template<class... xs>
    using f;
  }
#endif
  ;

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class C = identity>
  using is_unique = is_unique_if<same<>, C>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = typename detail::_unpack<mp::is_unique_if<mp::same<>, C>, L>::type;

    template<class L, class Cmp = mp::same<>, class C = mp::identity>
    using is_unique_if = typename detail::_unpack<mp::is_unique_if<Cmp, C>, L>::type;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp> // JLN_MP_MAKE_INTEGER_SEQUENCE
#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/detail/sequence.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/utility/inherit.hpp>
#include <jln/mp/utility/is_not.hpp>
#include <jln/mp/list/push_back.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_t i, class x>
  struct indexed_item : list<x>
  {};

  template<class, int_t... ints>
  struct indexed_inherit
  {
    template<class... xs>
    struct f : indexed_item<ints, xs>...
    {};
  };

#if JLN_MP_WORKAROUND(JLN_MP_GCC, < 1300)
# define JLN_MP_UNIQUE_WITH_REQUIRES 0
#else
# define JLN_MP_UNIQUE_WITH_REQUIRES JLN_MP_REQUIRES_AS_FAST_SFINAE
#endif

#if JLN_MP_MSVC_LIKE
  template<class... xs>
  struct _is_set
  {
    template<class Pack>
    static auto is_set(Pack pack) -> decltype((
        static_cast<list<xs>*>(pack),...
    ), number<1>());

    static number<0> is_set(...);

    using type = decltype(is_set(static_cast<
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)
      ::template f<xs...>*
    >(nullptr)));
  };

// 2% slower, but memoized
#elif JLN_MP_UNIQUE_WITH_REQUIRES

  template<int_t n>
  struct is_unique_impl
    : is_unique_impl<(
        n <= 15 ? n
      : n  < 30 ? 9'15
      : n == 30 ? 30
      : n  < 45 ? 9'30
      : n == 45 ? 45
      : n  < 60 ? 9'45
      : n == 60 ? 60
      : 9'60
    )>
  {};
  template<>
  struct is_unique_impl<0>
  {
    template<class...>
    using f = list<>;
  };

  template<>
  struct is_unique_impl<1>
    : identity
  {};

  template<>
  struct is_unique_impl<2>
  {
    template<class _1, class _2>
      requires
        (sizeof(inherit<_1, inherit<_2>>) == 1)
    using f = inherit<_1, inherit<_2>>;
  };

  template<>
  struct is_unique_impl<3>
  {
    template<class _1, class _2, class _3>
      requires
        (sizeof(inherit<_1, inherit<_2, inherit<_3>>>) == 1)
    using f = inherit<_1, inherit<_2, inherit<_3>>>;
  };

  template<>
  struct is_unique_impl<4>
  {
    template<class _1, class _2, class _3, class _4>
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4>>>
    >;
  };
  template<>
  struct is_unique_impl<5>
  {
    template<class _1, class _2, class _3, class _4, class _5>
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4, inherit<_5>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4, inherit<_5>>>>
    >;
  };

  template<>
  struct is_unique_impl<6>
  {
    template<class _1, class _2, class _3, class _4, class _5, class _6>
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6>>>
    >;
  };

  template<>
  struct is_unique_impl<7>
  {
    template<class _1, class _2, class _3, class _4, class _5, class _6, class _7>
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6, inherit<_7>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6, inherit<_7>>>>
    >;
  };
  template<>
  struct is_unique_impl<8>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4>>>,
          inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4>>>,
      inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>
    >;
  };

  template<>
  struct is_unique_impl<9>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4>>>,
          inherit<_5, inherit<_6, inherit<_7, inherit<_8, inherit<_9>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4>>>,
      inherit<_5, inherit<_6, inherit<_7, inherit<_8, inherit<_9>>>>>
    >;
  };

  template<>
  struct is_unique_impl<10>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6>>>,
          inherit<_7, inherit<_8, inherit<_9, inherit<_10>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6>>>,
      inherit<_7, inherit<_8, inherit<_9, inherit<_10>>>>
    >;
  };

  template<>
  struct is_unique_impl<11>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6>>>,
          inherit<_7, inherit<_8, inherit<_9, inherit<_10, inherit<_11>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6>>>,
      inherit<_7, inherit<_8, inherit<_9, inherit<_10, inherit<_11>>>>>
    >;
  };

  template<>
  struct is_unique_impl<12>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6, inherit<_7>>>>,
          inherit<_8, inherit<_9, inherit<_10, inherit<_11, inherit<_12>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6, inherit<_7>>>>,
      inherit<_8, inherit<_9, inherit<_10, inherit<_11, inherit<_12>>>>>
    >;
  };

  template<>
  struct is_unique_impl<13>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4>>>,
          inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>,
          inherit<_9, inherit<_10, inherit<_11, inherit<_12, inherit<_13>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4>>>,
      inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>,
      inherit<_9, inherit<_10, inherit<_11, inherit<_12, inherit<_13>>>>>
    >;
  };

  template<>
  struct is_unique_impl<14>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13, class _14
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3, inherit<_4>>>,
          inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>,
          inherit<_9, inherit<_10, inherit<_11, inherit<_12, inherit<_13, inherit<_14>>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3, inherit<_4>>>,
      inherit<_5, inherit<_6, inherit<_7, inherit<_8>>>>,
      inherit<_9, inherit<_10, inherit<_11, inherit<_12, inherit<_13, inherit<_14>>>>>>
    >;
  };

  template<>
  struct is_unique_impl<15>
  {
    template<
      class _1, class _2, class _3, class _4, class _5, class _6, class _7,
      class _8, class _9, class _10, class _11, class _12, class _13, class _14,
      class _15
    >
      requires
        (sizeof(inherit<
          _1,
          inherit<_2, inherit<_3>>,
          inherit<_4, inherit<_5, inherit<_6>>>,
          inherit<_7, inherit<_8, inherit<_9, inherit<_10>>>>,
          inherit<_11, inherit<_12, inherit<_13, inherit<_14, inherit<_15>>>>>
        >) == 1)
    using f = inherit<
      _1,
      inherit<_2, inherit<_3>>,
      inherit<_4, inherit<_5, inherit<_6>>>,
      inherit<_7, inherit<_8, inherit<_9, inherit<_10>>>>,
      inherit<_11, inherit<_12, inherit<_13, inherit<_14, inherit<_15>>>>>
    >;
  };


  template<>
  struct is_unique_impl<9'15>
  {
    template<JLN_MP_XS_15(class, JLN_MP_NIL, JLN_MP_COMMA), class... xs>
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(typename is_unique_impl<sizeof...(xs)>::template f<xs...>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      typename is_unique_impl<sizeof...(xs)>::template f<xs...>
    >;
  };

  template<>
  struct is_unique_impl<30>
  {
    template<
      JLN_MP_XS_15(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _16, class _17, class _18, class _19, class _20,
      class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>
      >
    >;
  };


  template<>
  struct is_unique_impl<9'30>
  {
    template<
      JLN_MP_XS_15(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _16, class _17, class _18, class _19, class _20,
      class _21, class _22, class _23, class _24, class _25,
      class _26, class _27, class _28, class _29, class _30,
      class... xs
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
        &&
        (sizeof(typename is_unique_impl<sizeof...(xs)>::template f<xs...>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>
      >,
      typename is_unique_impl<sizeof...(xs)>::template f<xs...>
    >;
  };

  template<>
  struct is_unique_impl<45>
  {
    template<
      JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42,
      class _43, class _44, class _45
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
        inherit<
          is_unique_impl<15>
            ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>
        >
      >
    >;
  };

  template<>
  struct is_unique_impl<9'45>
  {
    template<
      JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42,
      class _43, class _44, class _45, class... xs
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>) == 1)
        &&
        (sizeof(typename is_unique_impl<sizeof...(xs)>::template f<xs...>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
        inherit<
          is_unique_impl<15>
            ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>
        >
      >,
      typename is_unique_impl<sizeof...(xs)>::template f<xs...>
    >;
  };

  template<>
  struct is_unique_impl<60>
  {
    template<
      JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42,
      class _43, class _44, class _45, class _46, class _47,
      class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57,
      class _58, class _59, class _60
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
        inherit<
          is_unique_impl<15>
            ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>,
          inherit<
            is_unique_impl<15>
              ::f<_46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60>
          >
        >
      >
    >;
  };
  template<>
  struct is_unique_impl<9'60>
  {
    template<
      JLN_MP_XS_32(class, JLN_MP_NIL, JLN_MP_COMMA),
      class _33, class _34, class _35, class _36, class _37,
      class _38, class _39, class _40, class _41, class _42,
      class _43, class _44, class _45, class _46, class _47,
      class _48, class _49, class _50, class _51, class _52,
      class _53, class _54, class _55, class _56, class _57,
      class _58, class _59, class _60, class... xs
    >
      requires
        (sizeof(is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>) == 1)
        &&
        (sizeof(is_unique_impl<15>
          ::f<_46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60>) == 1)
        &&
        (sizeof(typename is_unique_impl<sizeof...(xs)>::template f<xs...>) == 1)
    using f = inherit<
      is_unique_impl<15>::f<JLN_MP_XS_15(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>,
      inherit<
        is_unique_impl<15>
          ::f<_16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30>,
        inherit<
          is_unique_impl<15>
            ::f<_31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45>,
          inherit<
            is_unique_impl<15>
              ::f<_46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60>
          >
        >
      >,
      inherit<typename is_unique_impl<sizeof...(xs)>::template f<xs...>>
    >;
  };
#endif
}

namespace jln::mp
{
  template<class C>
  struct is_unique_if<same<>, C>
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_set<xs...>::type);
#elif JLN_MP_UNIQUE_WITH_REQUIRES
    using f = JLN_MP_CALL_TRACE(C, number<requires{
      typename detail::is_unique_impl<sizeof...(xs)>
      ::template f<list<xs>...>;
    }>);
#else
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)
      ::template f<xs...>
    ) == 1>);
#endif
  };

  template<>
  struct is_unique_if<same<>, identity>
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = typename detail::_is_set<xs...>::type;
#elif JLN_MP_UNIQUE_WITH_REQUIRES
    using f = number<requires{
      typename detail::is_unique_impl<sizeof...(xs)>
      ::template f<list<xs>...>;
    }>;
#else
    using f = number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)
      ::template f<xs...>
    ) == 1>;
#endif
  };
}

namespace jln::mp::detail
{
  template<bool>
  struct is_unique_unpack_impl;

  template<>
  struct is_unique_unpack_impl<false>
  {
    template<class C, class seq, class... xs>
    using f = typename _unpack<C, seq, xs...>::type;
  };

  template<>
  struct is_unique_unpack_impl<true>
  {
    template<class C, class seq, class... xs>
    using f = void;
  };

  template<class C>
  struct is_unique_unpack
  {
    template<class seq, class... xs>
    using f = typename is_unique_unpack_impl<JLN_MP_IS_SAME(seq, void)>
      ::template f<C, seq, xs...>;
  };

  template<class Cmp>
  struct is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = JLN_MP_CONDITIONAL_P_C_T(
      (none_of<push_back<x, Cmp>>::template f<xs...>::value),
      (list<xs..., x>),
      (void)
    );
  };
}

namespace jln::mp
{
  template<class Cmp, class C>
  struct is_unique_if
    : push_front<
        list<>,
        fold<
          detail::is_unique_unpack<detail::is_unique_set_cmp_push_back_or_void<Cmp>>,
          is_not<void, C>
        >
      >
  {};
}

#undef JLN_MP_UNIQUE_WITH_REQUIRES
/// \endcond
