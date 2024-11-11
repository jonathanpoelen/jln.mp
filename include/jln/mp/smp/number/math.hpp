// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/math.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/functional/select.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using min = reverse_select_flip<less<>, C>;

  template<class C = identity>
  using max = reverse_select<less<>, C>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp_with = try_contract<mp::clamp_with<Min, Max, assume_binary<Cmp>, assume_unary<C>>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_with_c = try_contract<mp::clamp_with<number<min>, number<max>, assume_binary<Cmp>, assume_unary<C>>>;

  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = clamp_with<Min, Max, less<>, C>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp_with<number<min>, number<max>, Cmp, C>;


  template<class C = identity>
  using abs = try_contract<abs<assume_unary<C>>>;


  template<class C = identity>
  using pow = try_contract<pow<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Min, class Max, class Cmp, class C>
  struct _sfinae<sfinae, clamp_with<Min, Max, Cmp, C>>
  {
    using type = smp::clamp_with<Min, Max, sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, abs<C>>
  {
    using type = smp::abs<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, pow<C>>
  {
    using type = smp::pow<sfinae<C>>;
  };
}
/// \endcond
