#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/circulant_matrix.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_listify_or_monadic_xs_impl;

  template<class F, class C>
  using smp_listify_or_monadic_xs = typename smp_listify_or_monadic_xs_impl<
    std::is_same<F, smp::listify>::value>::template f<C>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F = listify, class C = listify>
  using circulant_matrix_with = contract<mp::circulant_matrix_with<
    assume_unary_or_more<F>, detail::smp_listify_or_monadic_xs<F, C>
  >>;

  template<class C = listify>
  using circulant_matrix = contract<mp::circulant_matrix<assume_lists<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, circulant_matrix_with<F, C>>
  {
    using type = smp::circulant_matrix_with<sfinae<F>, sfinae<C>>;
  };


  template<>
  struct smp_listify_or_monadic_xs_impl<false>
  {
    template<class C>
    using f = mp::monadic_xs<subcontract<C>>;
  };

  template<>
  struct smp_listify_or_monadic_xs_impl<true>
  {
    template<class C>
    using f = assume_lists<C>;
  };
}
/// \endcond
