// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/lift.hpp>

namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using lift = try_contract<mp::lift<F, assume_unary<C>>>;

  template<template<class...> class F, class C = identity>
  using lift_t = try_contract<mp::lift_t<F, assume_unary<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift_t<F, C>>
  {
    using type = smp::lift_t<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, lift<F, C>>
  {
    using type = smp::lift<F, sfinae<C>>;
  };
}
/// \endcond
