#pragma once

#include "../../algorithm/intersperse.hpp"
#include "../list/list.hpp"

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using intersperse = valid_contract<mp::intersperse<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, intersperse<x, C>>
  {
    using type = smp::intersperse<x, sfinae<C>>;
  };
}
