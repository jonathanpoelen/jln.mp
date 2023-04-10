#pragma once

#include <jln/mp/smp/algorithm/is_unique.hpp>
#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/map/is_map.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_map = contract<mp::is_map<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_map<C>>
  {
    using type = smp::is_map<sfinae<C>>;
  };
}
/// \endcond
