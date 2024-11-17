// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/capture_back.hpp>

namespace jln::mp::smp
{
  template<class... xs>
  using capture_back = try_contract<mp::capture_back<xs...>>;

  template<int_t... xs>
  using capture_back_c = try_contract<mp::capture_back_c<xs...>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, capture_back<xs...>>
  {
    using type = smp::capture_back<xs...>;
  };
}
/// \endcond
