#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/conjunction.hpp> // because conjunction is a index_if
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/compose.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class TC>
  using smp_index_if_cond = mp::if_<
    mp::front<smp::concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
    mp::size<
      mp::push_back<
        smp::sub<assume_positive_number_barrier<TC>>,
        mp::compose_f<mp::push_back, mp::size>
      >
    >,
    mp::always<violation>
  >;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = size<>>
  using index_if = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class T, class TC = identity, class FC = size<>>
  using index_of = contract<mp::index_if<is<T>, subcontract<TC>, subcontract<FC>>>;

  template<class Pred, class TC = identity, class FC = size<>>
  using index_if_xs = contract<mp::invoke_twice<
    mp::drop_while_xs<
      concepts::predicate<assume_unary_or_more<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary_or_more<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;

  template<int_ OffsetEnd, class Pred, class TC = identity, class FC = size<>>
  using partial_index_if_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_while_xs_c<
      OffsetEnd,
      concepts::predicate<assume_unary_or_more<Pred>, mp::not_<>>,
      detail::smp_index_if_cond<assume_unary_or_more<Pred>, TC>,
      mp::always<subcontract<FC>>
    >
  >>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(partial_index_if_xs,
  (OffsetEnd), (Pred), (TC, smp::listify), (FC, smp::size<>),
  smp::partial_index_if_xs_c<OffsetEnd::value, Pred, TC, FC>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, index_if<Pred, TC, FC>>
  {
    using type = smp::index_if<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, index_if_xs<Pred, TC, FC>>
  {
    using type = smp::index_if_xs<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, int_ OffsetEnd, class Pred, class TC, class FC>
  struct _sfinae<sfinae, partial_index_if_xs_c<OffsetEnd, Pred, TC, FC>>
  {
    using type = smp::partial_index_if_xs_c<OffsetEnd, sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
