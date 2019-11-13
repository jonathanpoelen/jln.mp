#pragma once

#include "../functional/identity.hpp"
#include "../../utility/same_as.hpp"

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using same_as = try_contract<mp::same_as<x, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, same_as<x, C>>
  {
    using type = smp::same_as<x, sfinae<C>>;
  };
}