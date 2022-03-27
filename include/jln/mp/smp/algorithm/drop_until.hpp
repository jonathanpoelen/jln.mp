#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<listify>>
  using drop_until = contract<mp::drop_until<
    concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
    mp::if_<
      mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
      assume_unary_or_more<TC>,
      violation
    >,
    subcontract<FC>
  >>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using drop_inclusive_until = drop_until<
    Pred, contract<mp::drop_front_c<1, subcontract<TC>>>, subcontract<FC>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, drop_until<Pred, TC, FC>>
  {
    using type = smp::drop_until<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
