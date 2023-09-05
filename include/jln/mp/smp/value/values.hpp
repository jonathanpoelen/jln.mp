// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/value/values.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using values = try_contract<mp::values<subcontract<C>>>;

  template<class C = listify>
  using typed_values = try_contract<mp::values<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, values<C>>
  {
    using type = smp::values<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, typed_values<C>>
  {
    using type = smp::typed_values<sfinae<C>>;
  };
}
/// \endcond
