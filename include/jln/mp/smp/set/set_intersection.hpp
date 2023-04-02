#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_intersection.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using set_intersection = test_contract<
    try_or<mp::pop_front<mp::all_of<mp::unpack<mp::is_unique<>>>>>,
    try_<mp::set_intersection<subcontract<C>>>
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, set_intersection<C>>
  {
    using type = smp::set_intersection<sfinae<C>>;
  };
}
/// \endcond
