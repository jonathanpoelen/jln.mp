#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
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
  template<class Pred, class C = listify>
  using take_while_xs = contract<mp::invoke_twice<
    mp::drop_while_xs<
      concepts::predicate<assume_unary_or_more<Pred>>,
      mp::if_<
        mp::if_<
          mp::size<>,
          mp::front<concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>>,
          mp::always<mp::true_>
        >,
        mp::size<
          mp::push_back<
            subcontract<C>,
            mp::lift<mp::drop_back>
          >
        >,
        mp::always<violation>
      >
    >
  >>;

  template<int_ OffsetEnd, class Pred, class C = listify>
  using partial_take_while_xs_c = contract<mp::invoke_twice<
    mp::partial_drop_while_xs<
      mp::number<OffsetEnd>,
      concepts::predicate<assume_unary_or_more<Pred>>,
      mp::if_<
        mp::if_<
          mp::size<>,
          mp::front<concepts::predicate<assume_unary_or_more<Pred>, mp::always<true_>>>,
          mp::always<mp::true_>
        >,
        mp::size<
          mp::push_back<
            subcontract<C>,
            mp::lift<mp::drop_back>
          >
        >,
        mp::always<violation>
      >
    >
  >>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(partial_take_while_xs, (OffsetEnd), (Pred), (C, smp::listify),
  smp::partial_take_while_xs_c<OffsetEnd::value, Pred, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, take_while_xs<Pred, C>>
  {
    using type = smp::take_while_xs<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class OffsetEnd, class Pred, class C>
  struct _sfinae<sfinae, partial_take_while_xs<OffsetEnd, Pred, C>>
  {
    using type = smp::partial_take_while_xs<OffsetEnd, sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
