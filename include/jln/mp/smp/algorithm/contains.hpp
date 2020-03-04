#pragma once

#include "../list/list.hpp"
#include "../../functional/monadic.hpp"
#include "../../algorithm/transform.hpp"

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform = contract<mp::transform<
    assume_unary<F>, mp::monadic_xs<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };
}
