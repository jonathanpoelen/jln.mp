#pragma once

#include "../assume.hpp"
#include "../functional/identity.hpp"
#include "../../utility/is.hpp"

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using is = try_contract<mp::is<x, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, is<x, C>>
  {
    using type = smp::is<x, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, is);
}
/// \endcond
