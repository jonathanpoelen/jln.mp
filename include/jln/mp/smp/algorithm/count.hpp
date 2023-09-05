// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/count.hpp>


namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<assume_positive_number_barrier<C>>>;

  template<class x, class C = identity>
  using count = contract<mp::count<x, assume_positive_number<C>>>;
}
