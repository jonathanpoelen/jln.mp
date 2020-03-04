#pragma once

#include "../functional/identity.hpp"
#include "../../value/as_val.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using as_val = try_contract<mp::as_val<assume_unary<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_val<C>>
  {
    using type = smp::as_val<sfinae<C>>;
  };
}
