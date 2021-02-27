#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/value/has_value.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using has_value = try_contract<mp::has_value<assume_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value<C>>
  {
    using type = smp::has_value<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_value);
}
/// \endcond
