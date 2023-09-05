// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/drop_until_xs.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_xs = contract<mp::drop_until_xs<
    concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_xs_c = contract<mp::partial_drop_until_xs_c<
    OffsetEnd,
    concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until_xs = drop_until_xs<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_inclusive_until_xs_c = partial_drop_until_xs_c<
    OffsetEnd, Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_until_extended_by_n_xs_c = drop_until_xs<
    Pred,
    contract<detail::smp_drop_front_or_drop_front_max_t<ExtendedByN, TC>>,
    FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC = listify, class FC = clear<TC>>
  using partial_drop_until_extended_by_n_xs_c = partial_drop_until_xs_c<
    OffsetEnd, Pred,
    contract<detail::smp_drop_front_or_drop_front_max_t<ExtendedByN, TC>>,
    FC>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_drop_until_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_drop_until_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(partial_drop_inclusive_until_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_drop_inclusive_until_xs_c<OffsetEnd::value, Pred, C>)

JLN_MP_MAKE_REGULAR_SMP4_P(drop_until_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::drop_until_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_drop_until_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, smp::clear<TC>),
  smp::partial_drop_until_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until_xs<Pred, TC, FC>>
  {
    using type = smp::drop_until_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_until_extended_by_n_xs_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_drop_until_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_drop_until_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
