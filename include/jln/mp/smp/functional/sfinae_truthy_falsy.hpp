// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/assume.hpp>

#include <jln/mp/functional/sfinae_truthy_falsy.hpp>

namespace jln::mp::smp
{
#if JLN_MP_FEATURE_CONCEPTS
  template<class Pred, class C = identity>
  using is_sfinae_truthy = contract<
    mp::is_sfinae_truthy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using is_sfinae_falsy = contract<
    mp::is_sfinae_falsy<assume_unary<Pred>, assume_number<C>>
  >;
#endif
} // namespace jln::mp::smp

#if JLN_MP_FEATURE_CONCEPTS
/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, is_sfinae_truthy<Pred, C>>
  {
    using type = smp::is_sfinae_truthy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, is_sfinae_falsy<Pred, C>>
  {
    using type = smp::is_sfinae_falsy<sfinae<Pred>, sfinae<C>>;
  };
} // namespace jln::mp::detail
/// \endcond
#endif
