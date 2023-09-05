// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/smp/functional/identity.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using as_bool = try_contract<mp::as_bool<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_bool<C>>
  {
    using type = smp::as_bool<sfinae<C>>;
  };
}
/// \endcond
