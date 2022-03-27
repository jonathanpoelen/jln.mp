#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/algorithm/take_while.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/algorithm/take_until.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = TC>
  using take_until = contract<mp::invoke_twice<
    mp::drop_until<
      concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
      mp::if_<
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        detail::smp_take_drop_for_size<TC>,
        mp::always<violation>
      >,
      mp::always<subcontract<FC>>
    >
  >>;

  template<class Pred, class TC = listify, class FC = TC>
  using take_inclusive_until = contract<mp::invoke_twice<
    mp::drop_until<
      concepts::predicate<assume_unary<Pred>, mp::identity, mp::always<true_>>,
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
  struct _sfinae<sfinae, take_until<Pred, TC, FC>>
  {
    using type = smp::take_until<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, take_inclusive_until<Pred, TC, FC>>
  {
    using type = smp::take_inclusive_until<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
