#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_back.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_back = contract<mp::bind_back<subcontract<F>, BoundArgs...>>;

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_back_c = bind_back<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_back_c = bind_back<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_back_v_c = try_contract<mp::bind_back_v_c<subcontract<F>, BoundArgs...>>;

  template<class F, class... xs>
  using bind_back_v = typename try_<
    mp::lift<mp::bind_back_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<subcontract<F>, xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_back<F, BoundArgs...>>
  {
    using type = smp::bind_back<sfinae<F>, BoundArgs...>;
  };

  template<template<class> class sfinae, class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct _sfinae<sfinae, bind_back_v_c<F, BoundArgs...>>
  {
    using type = smp::bind_back_v_c<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
