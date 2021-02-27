#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/smp/functional/identity.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using to_bool = try_contract<mp::to_bool<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, to_bool<C>>
  {
    using type = smp::to_bool<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, to_bool);
}
/// \endcond
