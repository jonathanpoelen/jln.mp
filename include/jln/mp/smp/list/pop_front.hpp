// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/list/pop_front.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using pop_front = drop_front_c<1, C>;
}
