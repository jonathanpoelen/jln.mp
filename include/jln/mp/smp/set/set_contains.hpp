// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_contains.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using set_contains = test_contract<
    mp::is_unique<>,
    mp::set_contains<x, subcontract<C>>
  >;

  template<class x, class C = identity>
  using set_all_contains = test_contract<
    mp::all_of<mp::try_or<mp::unpack<mp::is_unique<>>>>,
    mp::set_all_contains<x, subcontract<C>>
  >;

  template<class x, class C = identity>
  using set_any_contains = test_contract<
    mp::all_of<mp::try_or<mp::unpack<mp::is_unique<>>>>,
    mp::set_any_contains<x, subcontract<C>>
  >;

  template<class x, class C = identity>
  using set_none_contains = test_contract<
    mp::all_of<mp::try_or<mp::unpack<mp::is_unique<>>>>,
    mp::set_none_contains<x, subcontract<C>>
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_contains<x, C>>
  {
    using type = smp::set_contains<x, sfinae<C>>;
  };

  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_all_contains<x, C>>
  {
    using type = smp::set_all_contains<x, sfinae<C>>;
  };

  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_any_contains<x, C>>
  {
    using type = smp::set_any_contains<x, sfinae<C>>;
  };

  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_none_contains<x, C>>
  {
    using type = smp::set_none_contains<x, sfinae<C>>;
  };
}
/// \endcond
