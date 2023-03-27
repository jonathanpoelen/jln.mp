#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/alignof.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using alignof_ = try_contract<mp::alignof_<assume_positive_number<C>>>;
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

#include <jln/mp/smp/optimizer/optimizer.hpp>

JLN_MP_OPTIMIZER_CREATE_REGULAR_OPTIMIZER_0(mp::alignof_, 1, types::number);
/// \endcond
