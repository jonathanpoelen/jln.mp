// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/similar.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using similar = contract<mp::similar<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, similar<C>>
  {
    using type = smp::similar<sfinae<C>>;
  };
}
/// \endcond
