// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/number/numbers.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

namespace jln::mp::smp
{
  template<class C = numbers<>>
  using make_int_sequence_v = try_contract<
    mp::make_int_sequence_v<subcontract<C>>>;

  template<class C = listify>
  using make_int_sequence = make_int_sequence_v<numbers<C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, make_int_sequence_v<C>>
  {
    using type = smp::make_int_sequence_v<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::positive_number, make_int_sequence_v);
}
/// \endcond
