// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_is_unique;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class C = identity>
  using is_unique = typename detail::mk_is_unique<lift<std::is_same>, C>::type;

  /// Checks whether all \values are unique.
  /// \treturn \bool
  template<class Cmp = lift<std::is_same>, class C = identity>
  using is_unique_if = typename detail::mk_is_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = unpack<L, is_unique<C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::identity>
    using is_unique_if = unpack<L, is_unique_if<Cmp, C>>;
  }
}


#include <jln/mp/functional/tee.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/utility/is_not.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_ i, class x>
  struct indexed_item : basic_item<x> {};

  template<class, int_... ints>
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

  template<class C>
  struct is_unique_impl
  {
    template<class... xs>
#if JLN_MP_WORKAROUND(JLN_MP_MSVC_LIKE, < 1914)
    // workaround for MSVC which has a broken EBO
    using f = JLN_MP_CALL_TRACE(C, typename _is_set<xs...>::type);
#else
    using f = JLN_MP_CALL_TRACE(C, number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>
    ) == 1>);
#endif
  };

  template<>
  struct is_unique_impl<identity>
  {
    template<class... xs>
#if JLN_MP_MSVC_LIKE
    // workaround for MSVC which has a broken EBO
    using f = typename _is_set<xs...>::type;
#else
    using f = number<sizeof(
      typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), indexed_inherit)::template f<xs...>
    ) == 1>;
#endif
  };

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
    using f = typename is_unique_unpack_impl<std::is_same<seq, void>::value>
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

  template<class Cmp, class C>
  struct mk_is_unique
  {
    using type = push_front<list<>, fold<
      is_unique_unpack<is_unique_set_cmp_push_back_or_void<JLN_MP_TRACE_F(Cmp)>>,
      is_not<void, C>
    >>;
  };

  template<class C>
  struct mk_is_unique<lift<std::is_same>, C>
  {
    using type = is_unique_impl<C>;
  };

  template<class C>
  struct mk_is_unique<lift_t<std::is_same>, C>
  : mk_is_unique<lift<std::is_same>, C>
  {};

  template<class C>
  struct mk_is_unique<same<>, C>
  : mk_is_unique<lift<std::is_same>, C>
  {};
}
/// \endcond
