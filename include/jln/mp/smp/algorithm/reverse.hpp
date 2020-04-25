#pragma once

#include "../list/list.hpp"
#include "../../algorithm/reverse.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using reverse = contract<mp::reverse<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, reverse<C>>
  {
    using type = smp::reverse<sfinae<C>>;
  };
}
/// \endcond
