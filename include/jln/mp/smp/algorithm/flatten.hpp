// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/continuation.hpp>
#include <jln/mp/algorithm/flatten.hpp>

namespace jln::mp::smp
{
  template<class S = mp::cfe<list>, class C = listify>
  using flatten_once = try_contract<mp::flatten_once<S, subcontract<C>>>;

  template<class S = mp::cfe<list>, class C = listify>
  using flatten = try_contract<mp::flatten<S, subcontract<C>>>;

  template<template<class...> class S, class C = listify>
  using flatten_once_f = flatten_once<mp::cfe<S>, C>;

  template<template<class...> class S, class C = listify>
  using flatten_f = flatten<mp::cfe<S>, C>;

  template<template<class...> class S, class C = identity>
  using flatten_once_for_f = flatten<mp::cfe<S>, cfe<S, C>>;

  template<template<class...> class S, class C = identity>
  using flatten_for_f = flatten<mp::cfe<S>, cfe<S, C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class S, class C>
  struct _sfinae<sfinae, flatten_once<S, C>>
  {
    using type = smp::flatten_once<S, sfinae<C>>;
  };

  template<template<class> class sfinae, class S, class C>
  struct _sfinae<sfinae, flatten<S, C>>
  {
    using type = smp::flatten<S, sfinae<C>>;
  };
}
/// \endcond
