// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/fold.hpp>
#include <jln/mp/smp/functional/select.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/min_element.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using min_element_with = fold<reverse_select_flip<Cmp>, C>;

  template<class C = identity>
  using min_element = min_element_with<less<>, C>;


  template<class Cmp = less<>, class C = identity>
  using last_min_element_with = fold<select<Cmp>, C>;

  template<class C = identity>
  using last_min_element = last_min_element_with<less<>, C>;
}
