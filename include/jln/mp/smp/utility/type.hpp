// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/type.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using type_ = try_contract<mp::type_<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, type_<C>>
  {
    using type = smp::type_<sfinae<C>>;
  };
}
/// \endcond
