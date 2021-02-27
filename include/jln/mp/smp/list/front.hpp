#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using front = try_contract<mp::front<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, front<C>>
  {
    using type = smp::front<sfinae<C>>;
  };
}
/// \endcond
