#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/partition.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class F, class C>
  struct smp_partition_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class F = listify, class C = listify>
  using partition_with = try_contract<detail::smp_partition_with<
      assume_unary<Pred>, subcontract<F>, subcontract<C>>>;

  template<class Pred, class C = listify>
  using partition = partition_with<Pred, listify, assume_lists_barrier<C>>;
}


#include <jln/mp/functional/monadic.hpp>

/// \cond
namespace jln::mp::detail
{
  struct partition_caller_f
  {
    template<class... xs>
    using f = partition_impl<xs::value...>;
  };

  template<class Pred, class F, class C>
  struct smp_partition_with
  {
    template<class... xs>
    using f = typename mp::transform<
      Pred,
      mp::try_or<partition_caller_f, violation>
    >::template f<xs...>
     ::template f<mp::monadic_xs<C>::template f, F, xs...>;
  };

  template<template<class> class sfinae, class Pred, class F, class C>
  struct _sfinae<sfinae, partition_with<Pred, F, C>>
  {
    using type = smp::partition_with<sfinae<Pred>, sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
