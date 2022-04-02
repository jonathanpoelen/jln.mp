#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/capture_back.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class... xs>
  decltype(((void(xs::value), ...), try_contract<mp::capture_back_v<xs...>>{}))
  smp_capture_back_v(xs*...);

  bad_contract smp_capture_back_v(...);
}
/// \endcond

namespace jln::mp::smp
{
  template<class... xs>
  using capture_back = try_contract<mp::capture_back<xs...>>;

  template<class... xs>
  using capture_back_v = decltype(detail::smp_capture_back_v(static_cast<xs*>(nullptr)...));

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_c = capture_back<val<xs>...>;
#else
  template<int_... xs>
  using capture_back_c = capture_back<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_v_c = try_contract<mp::capture_back_v_c<xs...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_back<xs...>>
  {
    using type = smp::capture_back<xs...>;
  };

  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_back_v<xs...>>
  {
    using type = smp::capture_back_v<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_back_v_c<xs...>>
  {
    using type = smp::capture_back_v_c<xs...>;
  };
}
/// \endcond
