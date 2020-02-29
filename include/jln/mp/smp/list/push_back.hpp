#pragma once

#include "../list/list.hpp"
#include "../../list/push_back.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class x, class C = listify>
    using push_back = contract<mp::push_back<x, subcontract<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_back<x, C>>
  {
    using type = smp::push_back<x, sfinae<C>>;
  };
}
