#pragma once

#include "list.hpp"
#include "../../list/as_list.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using as_list = try_contract<mp::as_list<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_list<C>>
  {
    using type = smp::as_list<sfinae<C>>;
  };
}
