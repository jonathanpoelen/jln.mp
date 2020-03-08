#pragma once

#include "../contract.hpp"
#include "../list/list.hpp"
#include "../number/operators.hpp"
#include "../algorithm/is_sorted.hpp"
#include "../../algorithm/sort.hpp"
#include "../concepts.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using sort = try_contract<mp::sort<
    concepts::compare<Cmp, mp::identity, mp::always<true_>>,
    mp::if_<
      try_subcontract<is_sorted<Cmp>, mp::always<true_>, mp::always<false_>>,
      subcontract<C>,
      violation
    >
  >>;

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, sort<Cmp, C>>
  {
    using type = smp::sort<sfinae<Cmp>, sfinae<C>>;
  };
}
