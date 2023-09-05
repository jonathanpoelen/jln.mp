// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/capture_back.hpp>

namespace jln::mp::smp
{
  template<class... xs>
  using capture_back = try_contract<mp::capture_back<xs...>>;

#if __cplusplus >= 201703L
  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_c = capture_back<val<xs>...>;
#else
  template<int_... xs>
  using capture_back_c = capture_back<typed_val<int_, xs>...>;
#endif

  template<JLN_MP_TPL_AUTO_OR_INT... xs>
  using capture_back_v_c = try_contract<mp::capture_back_v_c<xs...>>;

  template<class... xs>
  using capture_back_v = typename try_<
    mp::lift<mp::capture_back_v, mp::lift<try_contract>>,
    mp::identity,
    always<bad_contract>
  >::template f<xs...>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_back<xs...>>
  {
    using type = smp::capture_back<xs...>;
  };

  template<template<class> class sfinae, JLN_MP_TPL_AUTO_OR_INT... xs>
  struct _sfinae<sfinae, capture_back_v_c<xs...>>
  {
    using type = smp::capture_back_v_c<xs...>;
  };
}
/// \endcond
