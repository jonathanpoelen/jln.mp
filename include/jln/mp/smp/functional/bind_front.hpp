#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, class... BoundArgs>
  decltype(((void(BoundArgs::value), ...), try_contract<mp::bind_front_v<F, BoundArgs...>>{}))
  smp_bind_front_v(BoundArgs*...);

  bad_contract smp_bind_front_v(...);
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_front = contract<mp::bind_front<subcontract<F>, BoundArgs...>>;

  template<class F, class... BoundArgs>
  using bind_front_v = decltype(detail::smp_bind_front_v(
    static_cast<F*>(nullptr), static_cast<BoundArgs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_front_c = bind_front<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_front_v_c = try_contract<mp::bind_front_v_c<F, BoundArgs...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_front<F, BoundArgs...>>
  {
    using type = smp::bind_front<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
