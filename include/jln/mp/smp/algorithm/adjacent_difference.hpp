#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/adjacent_difference.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using adjacent_difference = try_contract<mp::adjacent_difference<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, adjacent_difference<C>>
  {
    using type = smp::adjacent_difference<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, adjacent_difference);
}
/// \endcond
