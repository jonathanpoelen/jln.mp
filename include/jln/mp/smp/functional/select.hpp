// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/functional/select.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = TC>
  using select = if_<Pred, front<TC>, at1<FC>>;

  template<class Pred, class TC = identity, class FC = TC>
  using reverse_select = if_<Pred, at1<TC>, front<FC>>;
}
