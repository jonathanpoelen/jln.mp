#pragma once

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

  template<class C>
  struct expected_argument<is_val<C>>
  : number<argument_category::unary>
  {};
}
