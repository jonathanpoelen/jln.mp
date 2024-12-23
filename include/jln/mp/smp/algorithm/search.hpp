// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/algorithm/drop_until_xs.hpp>
#include <jln/mp/smp/algorithm/take_until_xs.hpp>
#include <jln/mp/algorithm/search.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search = drop_until_xs<Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using search_before = take_until_xs<Pred, TC, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n_c = take_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_c = partial_drop_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before_c = partial_take_until_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, Pred, TC, FC>;

  template<std::size_t StopWhenAtLeast, std::size_t ExtendedByN, class Pred,
           class TC = listify, class FC = clear<TC>>
  using partial_search_before_extended_by_n_c = partial_take_until_extended_by_n_xs_c<
    -JLN_MP_INTEGRAL_AS(int_t, StopWhenAtLeast)-1, ExtendedByN, Pred, TC, FC>;

  template<class ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using search_before_extended_by_n = take_until_extended_by_n_xs<ExtendedByN, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_search,
  (StopWhenAtLeast), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_search_c<StopWhenAtLeast::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_search_before_extended_by_n,
  (StopWhenAtLeast), (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_search_before_extended_by_n_c<
    StopWhenAtLeast::value, ExtendedByN::value, Pred, TC, FC>)

namespace jln::mp::smp
{
  template<class StopWhenAtLeast, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_search_before = partial_search_before_extended_by_n<StopWhenAtLeast, number<0>, Pred, TC, FC>;
}
