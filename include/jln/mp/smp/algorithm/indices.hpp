// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/make_int_sequence.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/algorithm/indices.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using indices = contract<mp::indices<assume_numbers<C>>>;
}
