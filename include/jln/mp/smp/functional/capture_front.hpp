#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/capture_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::capture_front_v<xs...>>{}))
  smp_capture_front_v(xs*...);

  bad_contract smp_capture_front_v(...);
}
/// \endcond

namespace jln::mp::smp
{
  template<class... xs>
  using capture_front = try_contract<mp::capture_front<xs...>>;

  template<class... xs>
  using capture_front_v = decltype(detail::smp_capture_front_v(static_cast<xs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_c = capture_front<val<xs>...>;
#else
  template<int_... xs>
  using capture_front_c = capture_front<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_front_v_c = try_contract<mp::capture_front_v_c<xs...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_front<xs...>>
  {
    using type = smp::capture_front<xs...>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_front_v<xs...>>
  {
    using type = smp::capture_front_v<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_front_v_c<xs...>>
  {
    using type = smp::capture_front_v_c<xs...>;
  };
}
/// \endcond
