#pragma once

#include "../list/list.hpp"
#include "../number/operators.hpp"
#include "../algorithm/is_sorted.hpp"
#include "../../functional/contract.hpp"
#include "../../algorithm/merge.hpp"
#include "../../list/at.hpp"
#include "../../list/is_list.hpp"
#include "../concepts.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using merge = contract<
    mp::if_<mp::at0<mp::is_list<>>, mp::at1<mp::is_list<>>>,
    mp::merge<
      concepts::predicate<Cmp, mp::identity, mp::always<true_>>,
      mp::if_<
        try_invoke<is_sorted<Cmp>, always<true_>, always<false_>>,
        subcontract<C>,
        violation
      >
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, merge<Cmp, C>>
  {
    using type = smp::merge<sfinae<Cmp>, sfinae<C>>;
  };
}
