#pragma once

#include "../functional/identity.hpp"
#include "../../algorithm/fold_right.hpp"
#include "../../functional/monadic.hpp"
#include "../../list/size.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_right = test_contract<
    mp::size<>,
    mp::fold_right<
      mp::monadic0<assume_unary<F>>,
      mp::monadic<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_right<F, C>>
  {
    using type = smp::fold_right<sfinae<F>, sfinae<C>>;
  };
}
