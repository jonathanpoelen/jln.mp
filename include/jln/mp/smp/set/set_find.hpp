// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_find.hpp>

namespace jln::mp::smp
{
  template<class x, class TC = identity, class FC = always<na>>
  using set_find = test_contract<
    mp::is_unique<>,
    mp::set_find<x, assume_unary<TC>, subcontract<FC>>
  >;

  template<class key, class FC>
  using set_find_or_else = set_find<key, identity, FC>;

  template<class key, class FT>
  using set_find_or = set_find<key, identity, always<FT>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class TC, class FC>
  struct _sfinae<sfinae, set_find<x, TC, FC>>
  {
    using type = smp::set_find<x, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
