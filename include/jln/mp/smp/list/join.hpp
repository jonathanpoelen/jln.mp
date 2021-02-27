#pragma once

#include <jln/mp/smp/list//listify.hpp>
#include <jln/mp/smp/algorithm/all_of.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using join = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::join<subcontract<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, join<C>>
  {
    using type = smp::join<sfinae<C>>;
  };
} // namespace jln::mp::detail
/// \endcond
