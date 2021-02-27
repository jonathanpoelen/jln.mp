#pragma once

#include "../assume.hpp"
#include "../functional/identity.hpp"
#include "../../utility/type.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using type_ = try_contract<mp::type_<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, type_<C>>
  {
    using type = smp::type_<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, type_);
}
/// \endcond
