#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/has_value_type.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using has_value_type = try_contract<mp::has_value_type<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_value_type<C>>
  {
    using type = smp::has_value_type<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_value_type);
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

JLN_MP_OPTIMIZER_CREATE_REGULAR_OPTIMIZER_0(mp::has_value_type, 1, types::boolean);
/// \endcond
