#pragma once

namespace jln::mp
{
  namespace detail
  {
    template <class L, class... Ts>
    struct _unpack;
  }

  template<class C>
  struct unpack
  {
    template<class... Ls>
    // TODO _unpack<C, Ls...> ?
    using f = typename detail::_unpack<Ls...>::template f<C>;
  };

  // TODO emp <L, C, xs...>
} // namespace jln::mp


#include "../list/list.hpp"

namespace jln::mp::detail
{
  template<template<class...> class Seq, class... Ts, class... xs>
  struct _unpack<Seq<Ts...>, xs...>
  {
    template<class C>
    using f = typename C::template f<xs..., Ts...>;
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

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
