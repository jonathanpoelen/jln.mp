// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/list/is_empty.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_empty = contract<mp::is_empty<assume_positive_number<C>>>;
}
