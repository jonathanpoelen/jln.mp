#pragma once

#include "../functional/bind.hpp"

namespace jln::mp
{
  template<class... vals>
  class list {};

  using listify = cfe<list>;
}

#include "../sfinae/sfinae_barrier.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = sfinae_barrier<listify>;
  };
}
