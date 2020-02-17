#pragma once

#include "../../functional/contract.hpp"
#include "../../algorithm/matrix_shortest.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using matrix_shortest = try_contract<mp::matrix_shortest<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, matrix_shortest<C>>
  {
    using type = smp::matrix_shortest<sfinae<C>>;
  };
}
