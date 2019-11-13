#pragma once

#include "split.hpp"
#include "../../algorithm/split_after.hpp"

namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using split_after_if = try_contract<
    mp::split_after_if<subcontract<Pred>, subcontract<C>>>;

  template<class x, class C = listify>
  using split_after = valid_contract<mp::split_after<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_after_if<F, C>>
  {
    using type = smp::split_after_if<sfinae<F>, sfinae<C>>;
  };
}
