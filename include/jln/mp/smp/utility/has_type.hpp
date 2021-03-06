#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/has_type.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using has_type = try_contract<mp::has_type<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, has_type<C>>
  {
    using type = smp::has_type<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, has_type);
}
/// \endcond
