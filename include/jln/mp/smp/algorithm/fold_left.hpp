#pragma once

#include "../functional/identity.hpp"
#include "../../algorithm/fold_left.hpp"
#include "../../functional/monadic.hpp"
#include "../../list/size.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using fold_left = test_contract<
    mp::size<>,
    mp::fold_left<
      mp::monadic0<subcontract<F>>,
      mp::monadic<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, fold_left<F, C>>
  {
    using type = smp::fold_left<sfinae<F>, sfinae<C>>;
  };
}
