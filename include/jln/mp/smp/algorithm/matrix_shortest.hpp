#pragma once

#include "../contract.hpp"
#include "../../algorithm/matrix_shortest.hpp"

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using matrix_shortest_with = try_contract<
    mp::matrix_shortest_with<subcontract<F>, subcontract<C>>>;

  template<class C = listify>
  using matrix_shortest = matrix_shortest_with<listify, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, matrix_shortest_with<F, C>>
  {
    using type = smp::matrix_shortest_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
