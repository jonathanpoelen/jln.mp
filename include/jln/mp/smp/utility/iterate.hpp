// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/iterate.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/list/is_size_of.hpp>

namespace jln::mp::smp
{
  template<uint_ n, class F, class C = identity>
  using iterate_c = test_contract<mp::is_size_of_c<1>, mp::iterate_c<
    n,
    mp::monadic0<assume_unary<F>>,
    mp::monadic0<assume_unary<C>>>
  >;
}

JLN_MP_MAKE_REGULAR_SMP3_P(iterate, (n), (F), (C, smp::identity),
    smp::iterate_c<mp::uint_{n::value}, F, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, uint_ n, class F, class C>
  struct _sfinae<sfinae, iterate_c<n, F, C>>
  {
    using type = smp::iterate_c<n, sfinae<F>, sfinae<C>>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp::optimizer
{
  template<class F, class C, class params>
  struct optimizer_impl<iterate_c<0, F, C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<lift<optimize>>
      ::template f<C, params>;
  };

  template<class F, class C, class params>
  struct optimizer_impl<iterate_c<1, F, C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<lift<optimize>>
      ::template f<tee<F, C>, params>;
  };

  struct optimized_for_iterate2
  {
    template<class params, class n, class F, class C>
    using f = typename callable_selector<output_result<F, params>>
      ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
      ::template f<C, types::any, lift<iterate>, n, F>;
  };

  template<uint_ n, class F, class C, class params>
  struct optimizer_impl<iterate_c<n, F, C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<optimized_for_iterate2>
      ::template f<params, number<n>, F, C>;
  };
}
/// \endcond
