// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/transform.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_transform;
}
/// \endcond

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform = typename detail::smp_transform<assume_unary<F>>
    ::template f<subcontract<C>>;
}


#include <jln/mp/algorithm/same_xs.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct smp_transform
  {
    template<class C>
    using f = contract<mp::transform<F, mp::monadic_xs<C>>>;
  };

  template<>
  struct smp_transform<listify>
  {
    template<class C>
    using f = contract<mp::transform<listify, C>>;
  };


  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };


  template<>
  struct optimize_useless_transform_unpack_impl<contract<identity>>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<contract<C>>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, C>>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<contract<transform<F, mp::monadic_xs<C>>>>
  {
    using type =
      typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<
        typename conditional_c<emp::same_xs_v<
          optimize_useless_transform_unpack_t<transform<F>>,
          transform<F>
        >>
        ::template f<mp::monadic_xs<C>, C>
      >;
  };
}
/// \endcond
