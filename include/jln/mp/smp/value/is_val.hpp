#pragma once

#include "../assume.hpp"
#include "../functional/identity.hpp"
#include "../../value/is_val.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using is_val = try_contract<mp::is_val<assume_number<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_val<C>>
  {
    using type = smp::is_val<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_val);
}
