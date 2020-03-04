#pragma once

#include "../list/list.hpp"
#include "../../functional/flip.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using flip = try_contract<mp::flip<assume_binary_or_more<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, flip<C>>
  {
    using type = smp::flip<sfinae<C>>;
  };

  template<class C>
  struct expected_argument<flip<C>>
  : number<argument_category::binary_or_more>
  {};
}
