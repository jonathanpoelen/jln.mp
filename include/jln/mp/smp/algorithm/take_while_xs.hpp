#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/take_while.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/take_while_xs.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

namespace jln::mp::smp
{
  template<std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using take_while_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::drop_while_xs<
      concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_while_xs = take_while_extended_by_n_xs_c<0, Pred, TC, FC>;

  template<int_ OffsetEnd, std::size_t ExtendedByN, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_extended_by_n_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_while_xs_c<
      OffsetEnd,
      concepts::predicate<assume_unary_or_more<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>,
        detail::smp_take_drop_for_size<ExtendedByN, TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_while_xs_c = partial_take_while_extended_by_n_xs_c<OffsetEnd, 0, Pred, TC, FC>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while_xs = take_while_extended_by_n_xs_c<1, Pred, TC, FC>;

  template<int_ OffsetEnd, class Pred, class TC = listify, class FC = TC>
  using partial_take_inclusive_while_xs_c = partial_take_while_extended_by_n_xs_c<
    OffsetEnd, 1, Pred, TC, FC>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(partial_take_inclusive_while_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_inclusive_while_xs_c<OffsetEnd::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP4_P(take_while_extended_by_n_xs,
  (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::take_while_extended_by_n_xs_c<ExtendedByN::value, Pred, TC, FC>)

JLN_MP_MAKE_REGULAR_SMP5_P(partial_take_while_extended_by_n_xs,
  (OffsetEnd), (ExtendedByN), (Pred), (TC, smp::listify), (FC, TC),
  smp::partial_take_while_extended_by_n_xs_c<OffsetEnd::value, ExtendedByN::value, Pred, TC, FC>)


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_xs<Pred, TC, FC>>
  {
    using type = smp::take_while_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, std::size_t ExtendedByN, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while_extended_by_n_xs_c<ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::take_while_extended_by_n_xs_c<
      ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };

  template<template<class> class sfinae, int_ OffsetEnd, std::size_t ExtendedByN,
           class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_take_while_extended_by_n_xs_c<OffsetEnd, ExtendedByN, Pred, TC, FC>>
  {
    using type = smp::partial_take_while_extended_by_n_xs_c<
      OffsetEnd, ExtendedByN, sfinae<Pred>, sfinae<TC>, sfinae<FC>
    >;
  };
}
/// \endcond
