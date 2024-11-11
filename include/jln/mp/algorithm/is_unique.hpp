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
    using is_unique = unpack<L, mp::is_unique_if<mp::same<>, C>>;

    template<class L, class Cmp = mp::same<>, class C = mp::identity>
    using is_unique_if = unpack<L, mp::is_unique_if<Cmp, C>>;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp> // JLN_MP_MAKE_INTEGER_SEQUENCE
#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/utility/is_not.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/set/set_contains.hpp> // basic_item

/// \cond
namespace jln::mp::detail
{
  template<int_t i, class x>
  struct indexed_item : basic_item<x>
  {};

  template<class, int_t... ints>
  struct indexed_inherit
  {
    template<class... xs>
    struct f : indexed_item<ints, xs>...
    {};
  };

#if JLN_MP_MSVC_LIKE
  template<class... xs>
  struct _is_set
  {
    template<class Pack>
    static auto is_set(Pack pack) -> decltype((
        static_cast<basic_item<xs>*>(pack),...
    ), number<1>());

    static number<0> is_set(...);

    using type = decltype(is_set(static_cast<
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>*
    >(nullptr)));
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
#else
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)::template f<xs...>
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
#else
    using f = number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), detail::indexed_inherit)::template f<xs...>
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
    using f = typename conditional_c<
      none_of<push_back<x, Cmp>>::template f<xs...>::value
    >::template f<list<xs..., x>, void>;
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
/// \endcond
