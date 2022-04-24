#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/algorithm/product.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using product = test_contract<
    mp::all_of<mp::is_list<>>,
    mp::product<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, product<C>>
  {
    using type = smp::product<sfinae<C>>;
  };
}
/// \endcond
