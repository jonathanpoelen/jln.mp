#pragma once

#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/algorithm/anticirculant_matrix.hpp>

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using anticirculant_matrix_with = contract<mp::anticirculant_matrix_with<
    assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using anticirculant_matrix = contract<mp::anticirculant_matrix<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, anticirculant_matrix_with<F, C>>
  {
    using type = smp::anticirculant_matrix_with<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
