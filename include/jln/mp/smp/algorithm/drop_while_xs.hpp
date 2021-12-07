#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using drop_while_xs = contract<mp::drop_while_xs<
    concepts::predicate<assume_unary_or_more<Pred>>,
    mp::if_<
      mp::if_<
        mp::size<>,
        mp::front<concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>>,
        mp::always<mp::true_>
      >,
      subcontract<C>,
      violation
    >
  >>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_drop_while_xs_c = contract<mp::partial_drop_while_xs_c<
    OffsetEnd,
    concepts::predicate<assume_unary_or_more<Pred>>,
    mp::if_<
      mp::if_<
        mp::size<>,
        mp::front<concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>>,
        mp::always<mp::true_>
      >,
      subcontract<C>,
      violation
    >
  >>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_drop_while_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_drop_while_xs_c<OffsetEnd::value, Pred, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, drop_while_xs<Pred, C>>
  {
    using type = smp::drop_while_xs<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, class Pred, class C>
  struct _sfinae<sfinae, partial_drop_while_xs_c<OffsetEnd, Pred, C>>
  {
    using type = smp::partial_drop_while_xs_c<OffsetEnd, sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
