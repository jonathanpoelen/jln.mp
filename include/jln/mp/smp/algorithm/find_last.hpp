// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/until_last.hpp>
#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/algorithm/find_last.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = until_last_t<drop_until, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = until_last_t<drop_while, Pred, TC, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = find_last_if<is<T>, TC, FC>;
}
