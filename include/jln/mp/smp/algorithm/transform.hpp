#pragma once

#include "../list/list.hpp"
#include "../../algorithm/transform.hpp"
#include "../../functional/monadic.hpp"


namespace jln::mp
{
  namespace smp
  {
    template<class F, class C = listify>
    using transform = valid_contract<mp::transform<
      subcontract<F>, mp::monadic_xs<subcontract<C>>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };
}
