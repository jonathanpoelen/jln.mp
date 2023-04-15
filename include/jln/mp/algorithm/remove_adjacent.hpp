#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/same.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct remove_adjacent_impl;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  struct remove_adjacent_if
  {
    template<class... xs>
    using f = typename detail::remove_adjacent_impl<rotate_c<-1>::f<xs...>>
      ::template f<JLN_MP_TRACE_F(C)::template f, BinaryPred, xs...>;
  };

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using remove_adjacent_if = unpack<L, mp::remove_adjacent_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using remove_adjacent = unpack<L, mp::remove_adjacent<C>>;
  }

  /// \cond
  template<class BinaryPred, template<class...> class C>
  struct remove_adjacent_if<BinaryPred, lift<C>>
  {
    template<class... xs>
    using f = typename detail::remove_adjacent_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, BinaryPred, xs...>;
  };
  /// \endcond
}


#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class BinaryPred, class x, class y>
  using remove_adjacent_transform = typename wrap_in_list_c<
    !BinaryPred::template f<x, y>::value
  >::template f<x>;

  template<class y, class... ys>
  struct remove_adjacent_impl<list<y, ys...>>
  {
    template<template<class...> class C, class BinaryPred, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(ys)+1>::template f<
      C,
      list<x>,
#if JLN_MP_GCC
      remove_adjacent_transform<JLN_MP_TRACE_F(BinaryPred), xs, ys>...
#else
      typename wrap_in_list_c<!JLN_MP_TRACE_F(BinaryPred)::template f<xs, ys>::value>
        ::template f<xs>...
#endif
    >::type;
  };

  template<class x>
  struct remove_adjacent_impl<list<x>>
  {
    template<template<class...> class C, class BinaryPred, class y>
    using f = C<y>;
  };

  template<>
  struct remove_adjacent_impl<list<>>
  {
    template<template<class...> class C, class BinaryPred, class... ys>
    using f = C<>;
  };
}
/// \endcond
