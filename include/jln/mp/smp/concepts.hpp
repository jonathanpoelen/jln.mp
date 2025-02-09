// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>

namespace jln::mp::smp::concepts
{
  // TODO optimize Pred = is<>, same<>, cfe<std::is_same>, equal, less, not_
  // {unary, binary, mulary}_predicate
  template<class Pred, class TC = mp::identity, class FC = mp::always<false_>>
  using predicate = mp::try_<Pred, mp::try_<mp::to_bool<>, TC, FC>, FC>;

  template<class Pred, class FC>
  using predicate_or_else = predicate<Pred, mp::identity, FC>;
}
