// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/functional/if.hpp>
#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<unsigned>
  struct smp_drop_front_or_drop_front_max;

  template<unsigned n, class C>
  using smp_drop_front_or_drop_front_max_t
    = typename smp_drop_front_or_drop_front_max<n < 2 ? n : 2>
    ::template f<n, subcontract<C>>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<listify>>
  using drop_while = contract<mp::drop_while<
    concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
    mp::if_<
      mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_while = drop_while<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, FC>;

  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = clear<TC>>
  using drop_while_extended_by_n_c = drop_while<
    Pred, contract<detail::smp_drop_front_or_drop_front_max_t<ExtendedByN, TC>>, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(drop_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, clear<TC>),
  smp::drop_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while<Pred, TC, FC>>
  {
    using type = smp::drop_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::drop_while_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };


  template<>
  struct smp_drop_front_or_drop_front_max<0>
  {
    template<unsigned, class C>
    using f = C;
  };

  template<>
  struct smp_drop_front_or_drop_front_max<1>
  {
    template<unsigned, class C>
    using f = mp::drop_front_c<1, C>;
  };

  template<>
  struct smp_drop_front_or_drop_front_max<2>
  {
    template<unsigned n, class C>
    using f = mp::drop_front_max_c<n, C>;
  };
}
/// \endcond
