// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/continuation.hpp>

namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using cfe = try_contract<mp::cfe<F, assume_unary<C>>>;

  template<template<class...> class F, class C = identity>
  using cfl = try_contract<mp::cfl<F, assume_unary<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfl<F, C>>
  {
    using type = smp::cfl<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfe<F, C>>
  {
    using type = smp::cfe<F, sfinae<C>>;
  };
}
/// \endcond
