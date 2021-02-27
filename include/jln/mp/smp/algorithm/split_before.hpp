#pragma once

#include <jln/mp/smp/algorithm/split.hpp>
#include <jln/mp/algorithm/split_before.hpp>

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_before_if = try_contract<
    mp::split_before_if<assume_unary<Pred>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split_before = contract<mp::split_before<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_before_if<F, C>>
  {
    using type = smp::split_before_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
