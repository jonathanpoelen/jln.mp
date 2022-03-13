#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/list/join.hpp>
#include <jln/mp/algorithm/partition.hpp>

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using partition_with = mp::partition_with<
      try_assume_unary<Pred>, subcontract<F>, subcontract<C>>;

  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, partition_with<Pred, F, C>>
  {
    using type = smp::partition_with<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
