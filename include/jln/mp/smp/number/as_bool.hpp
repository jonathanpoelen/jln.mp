#pragma once

#include "../../number/as_bool.hpp"
#include "../functional/identity.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using as_bool = try_contract<mp::as_bool<assume_unary<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_bool<C>>
  {
    using type = smp::as_bool<sfinae<C>>;
  };
}
