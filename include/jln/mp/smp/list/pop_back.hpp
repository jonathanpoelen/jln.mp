// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/list/pop_back.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using pop_back = rotate_c<-1, pop_front<C>>;
}
