#pragma once

#include "../contract.hpp"
#include "../list/listify.hpp"
#include "../number/operators.hpp"
#include "../algorithm/is_sorted.hpp"
#include "../../algorithm/merge.hpp"
#include "../../list/at.hpp"
#include "../../list/is_list.hpp"
#include "../concepts.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = listify>
  using merge = test_contract<
    mp::if_<mp::at0<mp::is_list<>>, mp::at1<mp::is_list<>>>,
    mp::merge<
      concepts::predicate<assume_binary<Cmp>, mp::identity, mp::always<true_>>,
      mp::if_<
        try_subcontract<is_sorted<Cmp>, mp::always<true_>, mp::always<false_>>,
        subcontract<C>,
        violation
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, merge<Cmp, C>>
  {
    using type = smp::merge<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
