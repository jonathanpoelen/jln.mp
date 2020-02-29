#pragma once

#include "../functional/identity.hpp"
#include "../../utility/always.hpp"

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using always = contract<mp::always<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class T, class C>
  struct _sfinae<sfinae, always<T, C>>
  {
    using type = smp::always<T, sfinae<C>>;
  };
}
