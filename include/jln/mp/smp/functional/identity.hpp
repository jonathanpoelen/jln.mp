#pragma once

#include "../../functional/identity.hpp"
#include "../../functional/try_invoke.hpp"
#include "../../functional/sfinaefwd.hpp"

namespace jln::mp::smp
{
  using identity = valid_contract<mp::try_invoke<mp::identity>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, identity>
  {
    using type = smp::identity;
  };
}
