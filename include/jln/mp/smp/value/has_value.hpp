#pragma once

#include "../functional/identity.hpp"
#include "../../value/has_value.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using has_value = try_contract<mp::has_value<assume_number<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value<C>>
  {
    using type = smp::has_value<sfinae<C>>;
  };

  template<class C>
  struct expected_argument<has_value<C>>
  : number<argument_category::unary>
  {};
}
