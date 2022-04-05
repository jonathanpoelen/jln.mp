#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/capture_front.hpp>

namespace jln::mp::smp
{
  template<class... xs>
  using capture_front = try_contract<mp::capture_front<xs...>>;

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_c = capture_front<val<xs>...>;
#else
  template<int_... xs>
  using capture_front_c = capture_front<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_v_c = try_contract<mp::capture_front_v_c<xs...>>;

  template<class... xs>
  using capture_front_v = typename try_<
    mp::lift<mp::capture_front_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_front<xs...>>
  {
    using type = smp::capture_front<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_front_v_c<xs...>>
  {
    using type = smp::capture_front_v_c<xs...>;
  };
}
/// \endcond
