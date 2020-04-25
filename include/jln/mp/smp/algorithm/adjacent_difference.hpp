#pragma once

#include "../list/list.hpp"
#include "../../algorithm/adjacent_difference.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using adjacent_difference = adjacent_difference<subcontract<C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, adjacent_difference<C>>
  {
    using type = smp::adjacent_difference<sfinae<C>>;
  };
}
/// \endcond
