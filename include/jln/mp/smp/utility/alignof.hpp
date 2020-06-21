#pragma once

#include "../functional/identity.hpp"
#include "../../utility/alignof.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using alignof_ = try_contract<mp::alignof_<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, alignof_<C>>
  {
    using type = smp::alignof_<sfinae<C>>;
  };
}
/// \endcond
