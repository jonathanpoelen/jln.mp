#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/bind_front.hpp>

namespace jln::mp::smp
{
  template<class F, class... BoundArgs>
  using bind_front = contract<mp::bind_front<subcontract<F>, BoundArgs...>>;

#if __cplusplus >= 201703L
  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_front_c = bind_front<F, val<BoundArgs>...>;
#else
  template<class F, int_... BoundArgs>
  using bind_front_c = bind_front<F, typed_val<int_, BoundArgs>...>;
#endif

  template<class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  using bind_front_v_c = try_contract<mp::bind_front_v_c<subcontract<F>, BoundArgs...>>;

  template<class F, class... xs>
  using bind_front_v = typename try_<
    mp::lift<mp::bind_front_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<subcontract<F>, xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... BoundArgs>
  struct _sfinae<sfinae, bind_front<F, BoundArgs...>>
  {
    using type = smp::bind_front<sfinae<F>, BoundArgs...>;
  };

  template<template<class> class sfinae, class F, JLN_MP_TPL_AUTO_OR_INT... BoundArgs>
  struct _sfinae<sfinae, bind_front_v_c<F, BoundArgs...>>
  {
    using type = smp::bind_front_v_c<sfinae<F>, BoundArgs...>;
  };
}
/// \endcond
