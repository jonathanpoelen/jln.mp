#pragma once

#include "../assume.hpp"
#include "../../number/to_bool.hpp"
#include "../functional/identity.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using to_bool = try_contract<mp::to_bool<assume_unary<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, to_bool<C>>
  {
    using type = smp::to_bool<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, to_bool);
}
