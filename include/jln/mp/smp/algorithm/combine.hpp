#pragma once

#include "../list/list.hpp"
#include "../../algorithm/combine.hpp"


namespace jln::mp::smp
{
  template<class C = listify>
  using combine = contract<mp::combine<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, combine<C>>
  {
    using type = smp::combine<sfinae<C>>;
  };
}
