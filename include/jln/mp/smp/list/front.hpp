#pragma once

#include "../functional/identity.hpp"
#include "../../list/front.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class C = listify>
    using front = try_contract<mp::front<subcontract<C>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, front<C>>
  {
    using type = smp::front<sfinae<C>>;
  };
}
