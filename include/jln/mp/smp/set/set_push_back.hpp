#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_push_back.hpp>

namespace jln::mp::smp
{
  template<class x, class C = listify>
  using set_push_back = test_contract<
    mp::is_unique<>,
    mp::set_push_back<x, assume_unary_or_more<C>>
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class C>
  struct _sfinae<sfinae, set_push_back<x, C>>
  {
    using type = smp::set_push_back<x, sfinae<C>>;
  };
}
/// \endcond
