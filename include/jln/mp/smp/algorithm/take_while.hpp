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
  template<class TC>
  using smp_take_drop_for_size = mp::size<
    mp::push_back<
      subcontract<TC>,
      mp::lift<mp::drop_back>
    >
  >;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using take_while = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        detail::smp_take_drop_for_size<TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_while = contract<mp::invoke_twice<
    mp::drop_while<
      concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<false_>>,
      mp::if_<
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        mp::drop_front_c<
          1,
          detail::smp_take_drop_for_size<TC>
        >,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_while<Pred, TC, FC>>
  {
    using type = smp::take_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_inclusive_while<Pred, TC, FC>>
  {
    using type = smp::take_inclusive_while<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
