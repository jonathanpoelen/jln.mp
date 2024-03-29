// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/find.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if = drop_until<Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_if_not = drop_while<Pred, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find = contract<mp::find<T, assume_unary_or_more<TC>, subcontract<FC>>>;
}
