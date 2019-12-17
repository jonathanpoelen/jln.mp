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
} // namespace jln::mp

namespace jln::mp::detail
{
  template<template<class...> class Seq, class... Ts, class... xs>
  struct _unpack<Seq<Ts...>, xs...>
  {
    template<class C>
    using f = typename C::template f<xs..., Ts...>;
  };
}
