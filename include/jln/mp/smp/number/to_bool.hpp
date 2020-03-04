#pragma once

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

  template<class C>
  struct expected_argument<to_bool<C>>
  : number<argument_category::unary>
  {};
}
