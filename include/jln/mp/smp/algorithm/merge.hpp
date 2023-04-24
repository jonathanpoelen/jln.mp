#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/algorithm/is_sorted.hpp>
#include <jln/mp/algorithm/merge.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/smp/concepts.hpp>

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
