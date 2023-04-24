#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/utility/is_not.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using is_not = try_contract<mp::is<x, mp::not_<assume_positive_number<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, is<x, not_<C>>>
  {
    using type = smp::is_not<x, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, is_not);
}
/// \endcond
