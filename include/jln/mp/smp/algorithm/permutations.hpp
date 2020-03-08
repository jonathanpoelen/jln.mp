#pragma once

#include "../contract.hpp"
#include "../../algorithm/permutations.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using permutations = try_contract<permutations<assume_lists<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, permutations<C>>
  {
    using type = smp::permutations<sfinae<C>>;
  };
}
