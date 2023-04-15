#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/join.hpp> // for remove_adjacent
#include <jln/mp/smp/list/pop_front.hpp> // for remove_adjacent
#include <jln/mp/smp/functional/if.hpp> // for remove_adjacent
#include <jln/mp/smp/utility/always.hpp> // for remove_adjacent
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/pairwise_fold.hpp>

namespace jln::mp::smp
{
  template<class F, class Front = identity, class C = listify>
  using pairwise_fold_and_transform_front = try_contract<mp::pairwise_fold_and_transform_front<
    assume_binary<F>, assume_unary<Front>, mp::monadic_xs<C>
  >>;

  template<class F, class C = listify>
  using pairwise_fold = try_contract<mp::pairwise_fold_and_transform_front<
    assume_binary<F>, mp::identity, mp::monadic_xs<C>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class Front, class C>
  struct _sfinae<sfinae, pairwise_fold_and_transform_front<F, Front, C>>
  {
    using type = smp::pairwise_fold_and_transform_front<sfinae<F>, sfinae<Front>, sfinae<C>>;
  };
}
/// \endcond
