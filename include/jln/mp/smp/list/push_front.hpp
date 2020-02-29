#pragma once

#include "../list/list.hpp"
#include "../../list/push_front.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class x, class C = listify>
    using push_front = contract<mp::push_front<x, subcontract<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, push_front<x, C>>
  {
    using type = smp::push_front<x, sfinae<C>>;
  };
}
