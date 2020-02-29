#pragma once

#include "split.hpp"
#include "../../algorithm/split_before.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_before_if = try_contract<
    mp::split_before_if<subcontract<Pred>, subcontract<C>>>;

  template<class x, class C = listify>
  using split_before = contract<mp::split_before<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_before_if<F, C>>
  {
    using type = smp::split_before_if<sfinae<F>, sfinae<C>>;
  };
}
