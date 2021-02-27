#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/fold_left.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_left = test_contract<
    mp::size<>,
    mp::fold_left<
      mp::monadic0<assume_binary<F>>,
      mp::monadic<assume_unary<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_left<F, C>>
  {
    using type = smp::fold_left<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
