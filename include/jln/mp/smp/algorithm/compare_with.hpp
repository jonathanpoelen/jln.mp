// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/each.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/compare_with.hpp>


namespace jln::mp::smp
{
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, assume_binary<Cmp>>;
}
