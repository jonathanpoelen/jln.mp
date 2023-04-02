#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_push_front.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using set_push_front = test_contract<mp::is_unique<>, mp::set_push_front<x, subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_push_front<x, C>>
  {
    using type = smp::set_push_front<x, sfinae<C>>;
  };
}
/// \endcond
