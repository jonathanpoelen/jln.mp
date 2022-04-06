#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/assume.hpp>
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

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary_or_more, front);
}
/// \endcond
