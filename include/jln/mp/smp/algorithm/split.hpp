#pragma once

#include "../list/list.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/split.hpp"

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using split_if = try_contract<
    mp::split_if<subcontract<F>, subcontract<C>>>;

  template<class x, class C = listify>
  using split = contract<mp::split<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_if<F, C>>
  {
    using type = smp::split_if<sfinae<F>, sfinae<C>>;
  };
}

