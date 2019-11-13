#pragma once

#include "../functional/identity.hpp"
#include "../../list/size.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using size = valid_contract<mp::size<assume_number<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, size<C>>
  {
    using type = smp::size<sfinae<C>>;
  };
}