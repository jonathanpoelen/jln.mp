#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/take_while.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

/// \cond
namespace jln::mp::detail
{
  template<std::size_t ExtendedByN, class C>
  struct smp_take_drop_for_size
  {
    template<class... xs>
    using f = mp::drop_back_c<
      sizeof...(xs) >= ExtendedByN ? sizeof...(xs) - ExtendedByN : 0,
      subcontract<C>
    >;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_c = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_while = take_while_extended_by_n_c<0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = take_while_extended_by_n_c<1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(take_while_extended_by_n,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_while_extended_by_n_c<ExtendedByN::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while<Pred, TC, FC>>
  {
    using type = smp::take_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_extended_by_n_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_while_extended_by_n_c<ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
