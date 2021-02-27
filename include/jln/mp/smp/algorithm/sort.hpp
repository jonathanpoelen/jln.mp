#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/algorithm/is_sorted.hpp>
#include <jln/mp/algorithm/sort.hpp>
#include <jln/mp/smp/concepts.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using sort = try_contract<mp::sort<
    concepts::predicate<assume_binary<Cmp>, mp::identity, mp::always<true_>>,
    mp::if_<
      try_subcontract<is_sorted<Cmp>, mp::always<true_>, mp::always<false_>>,
      subcontract<C>,
      violation
    >
  >>;

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, sort<Cmp, C>>
  {
    using type = smp::sort<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
