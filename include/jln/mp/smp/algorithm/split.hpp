#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/split.hpp>

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using split_if = try_contract<
    mp::split_if<assume_unary<F>, assume_lists<C>>>;

  template<class x, class C = listify>
  using split = contract<mp::split<x, assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, split_if<F, C>>
  {
    using type = smp::split_if<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
