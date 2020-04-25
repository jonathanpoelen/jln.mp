#pragma once

#include "../contract.hpp"
#include "../../functional/fix.hpp"

namespace jln::mp::smp
{
  template <class C>
  using fix = try_contract<fix<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, fix<C>>
  {
    using type = smp::fix<sfinae<C>>;
  };
}
/// \endcond
