#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_back.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, class... BoundArgs>
  decltype(((void(BoundArgs::value), ...), try_contract<mp::bind_back_v<F, BoundArgs...>>{}))
  smp_bind_back_v(BoundArgs*...);

  bad_contract smp_bind_back_v(...);
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_back = contract<mp::bind_back<subcontract<F>, BoundArgs...>>;

  template<class F, class... BoundArgs>
  using bind_back_v = decltype(detail::smp_bind_back_v(
    static_cast<F*>(nullptr), static_cast<BoundArgs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_back_c = bind_back<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_back_v_c = try_contract<mp::bind_back_v_c<F, BoundArgs...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_back<F, BoundArgs...>>
  {
    using type = smp::bind_back<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
