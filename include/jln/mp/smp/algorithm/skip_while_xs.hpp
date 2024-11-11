// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/skip_while_xs.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using skip_while_xs = drop_while_xs<Pred, TC, clear<FC>>;

  template<class Pred, class TC = listify, class FC = TC>
  using skip_inclusive_while_xs = drop_inclusive_while_xs<Pred, TC, clear<FC>>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs
    = drop_while_extended_by_n_xs<ExtendedByN, Pred, TC, clear<FC>>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using skip_while_extended_by_n_xs_c
    = drop_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs = partial_drop_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_xs_c = partial_drop_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs
    = partial_drop_inclusive_while_xs<OffsetEnd, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_skip_inclusive_while_xs_c
    = partial_drop_inclusive_while_xs_c<OffsetEnd, Pred, TC, clear<FC>>;

  template<class OffsetEnd, class ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs
    = partial_drop_while_extended_by_n_xs<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_skip_while_extended_by_n_xs_c
    = partial_drop_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, clear<FC>>;
}
