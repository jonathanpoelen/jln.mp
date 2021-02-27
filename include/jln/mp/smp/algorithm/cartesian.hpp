#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/algorithm/cartesian.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using cartesian = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::cartesian<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, cartesian<C>>
  {
    using type = smp::cartesian<sfinae<C>>;
  };
}
/// \endcond
