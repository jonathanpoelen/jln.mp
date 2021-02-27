#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/value/as_val.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using as_val = try_contract<mp::as_val<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_val<C>>
  {
    using type = smp::as_val<sfinae<C>>;
  };
}
/// \endcond
