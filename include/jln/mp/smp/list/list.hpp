#pragma once

#include "../../list/list.hpp"
#include "../../functional/contract.hpp"
#include "../../functional/sfinaefwd.hpp"

namespace jln::mp::smp
{
  using listify = contract<mp::listify>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = smp::listify;
  };
}
