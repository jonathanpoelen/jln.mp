// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/same.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using same = contract<mp::same<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, same<C>>
  {
    using type = smp::same<sfinae<C>>;
  };
}
/// \endcond
