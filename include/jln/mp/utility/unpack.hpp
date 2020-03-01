#pragma once

namespace jln::mp
{
  namespace detail
  {
    template <class L> struct _unpack;
    template <class L> struct _unpack_append;
  }

  template<class C>
  struct unpack
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack<seq>::template f<C, xs...>;
  };

  template<class C>
  struct unpack_append
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append<seq>::template f<C, xs...>;
  };
  
  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<L>::template f<C, xs...>;
    
    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<L>::template f<C, xs...>;
  }
} // namespace jln::mp


#include "../list/list.hpp"

namespace jln::mp::detail
{
  template<template<class...> class Seq, class... ys>
  struct _unpack<Seq<ys...>>
  {
    template<class C, class... xs>
    using f = typename C::template f<xs..., ys...>;
  };

  template<template<class...> class Seq, class... xs>
  struct _unpack_append<Seq<xs...>>
  {
    template<class C, class... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class C>
  struct optimize_useless_unpack
  {
    using type = C;
  };

  template<>
  struct optimize_useless_unpack<unpack<listify>>
  {
    using type = identity;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<listify>>
  {
    using type = identity;
  };

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
