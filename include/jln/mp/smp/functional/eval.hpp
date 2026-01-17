// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/eval.hpp>

#if JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS
/// \cond
#if !JLN_MP_GCC
namespace jln::mp::detail
{
  template<auto F, class... xs>
    requires(requires {
      // bug 5818686
      #if JLN_MP_CUDA
      static_cast<decltype(F) const&>(F)
      #else
      F
      #endif
      .template operator()<xs...>();
    })
  struct smp_func
  {
    using type = decltype(F.template operator()<xs...>());
  };

  template<auto F, class C = identity>
  struct smp_eval
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename smp_func<F, xs...>::type);
  };

  template<auto F>
  struct smp_eval<F, identity>
  {
    template<class... xs>
    using f = typename smp_func<F, xs...>::type;
  };
}
#endif
/// \endcond

namespace jln::mp::smp
{
#if !JLN_MP_GCC
  template<auto F, class C = identity>
  using eval = try_contract<detail::smp_eval<F, assume_unary<C>>>;
#else
  template<auto F, class C = identity>
  using eval = try_contract<eval<F, assume_unary<C>>>;
#endif
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, auto F, class C>
  struct _sfinae<sfinae, eval<F, C>>
  {
    using type = smp::eval<F, sfinae<C>>;
  };
}
/// \endcond

#endif
