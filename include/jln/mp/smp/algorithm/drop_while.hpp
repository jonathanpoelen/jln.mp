#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/drop_while.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using drop_while = contract<mp::drop_while<
    concepts::predicate<assume_unary<Pred>>,
    mp::if_<
      mp::if_<
        mp::size<>,
        mp::front<concepts::predicate<assume_unary<Pred>, mp::always<true_>>>,
        mp::always<mp::true_>
      >,
      subcontract<C>,
      violation
    >
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, drop_while<Pred, C>>
  {
    using type = smp::drop_while<sfinae<Pred>, sfinae<C>>;
  };
}
/// \endcond
