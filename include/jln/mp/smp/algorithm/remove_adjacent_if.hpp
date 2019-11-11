#pragma once

#include "../list/list.hpp"
#include "../../algorithm/remove_adjacent_if.hpp"

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using remove_adjacent_if = try_contract<mp::remove_adjacent_if<
    subcontract<F>, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, remove_adjacent_if<Cmp, C>>
  {
    using type = smp::remove_adjacent_if<sfinae<Cmp>, sfinae<C>>;
  };
}
