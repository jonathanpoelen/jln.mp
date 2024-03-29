// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/functional/apply_or_identity.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC>
  using apply_or_identity = if_<Pred, TC, identity>;
}
