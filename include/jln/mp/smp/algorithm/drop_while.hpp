#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<listify>>
  using drop_while = contract<mp::drop_while<
    concepts::strong_predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
    mp::if_<
      mp::front<concepts::strong_predicate<assume_unary<Pred>, mp::always<true_>>>,
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
    Pred, contract<mp::drop_front_max_c<ExtendedByN, subcontract<TC>>>, FC>;
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
}
/// \endcond
