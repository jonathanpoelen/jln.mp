#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/pairwise.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/algorithm/is_sorted.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using is_sorted = contract<mp::pairwise_with<
    assume_binary<Cmp>, and_<assume_positive_number_barrier<C>>
  >>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_sorted<Cmp, C>>
  {
    using type = smp::is_sorted<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
