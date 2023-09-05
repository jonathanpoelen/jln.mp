// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/list/is_not_empty.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_not_empty = contract<mp::is_not_empty<assume_positive_number<C>>>;
}
