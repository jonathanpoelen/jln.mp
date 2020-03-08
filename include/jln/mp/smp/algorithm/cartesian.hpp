#pragma once

#include "../list/list.hpp"
#include "../../list/is_list.hpp"
#include "../../number/operators.hpp"
#include "../../algorithm/all_of.hpp"
#include "../../algorithm/cartesian.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using cartesian = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::cartesian<assume_lists<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, cartesian<C>>
  {
    using type = smp::cartesian<sfinae<C>>;
  };
}
