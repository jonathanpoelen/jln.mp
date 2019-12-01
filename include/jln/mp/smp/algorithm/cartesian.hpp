#pragma once

#include "../list/list.hpp"
#include "../../list/is_list.hpp"
#include "../../number/operators.hpp"
#include "../../algorithm/transform.hpp"
#include "../../algorithm/cartesian.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using cartesian = contract<
    mp::transform<mp::is_list<>, mp::and_<>>,
    mp::cartesian<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, cartesian<C>>
  {
    using type = smp::cartesian<sfinae<C>>;
  };
}
