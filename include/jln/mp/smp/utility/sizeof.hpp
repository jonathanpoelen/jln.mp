#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/sizeof.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using sizeof_ = try_contract<mp::sizeof_<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sizeof_<C>>
  {
    using type = smp::sizeof_<sfinae<C>>;
  };
}
/// \endcond
