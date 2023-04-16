#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/algorithm/reverse_fold_right.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using reverse_fold_right = test_contract<
    mp::size<>,
    mp::reverse_fold_right<
      mp::monadic0<assume_unary<F>>,
      mp::monadic<subcontract<C>>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, reverse_fold_right<F, C>>
  {
    using type = smp::reverse_fold_right<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
