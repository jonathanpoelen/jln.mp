// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/math.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/algorithm/fold.hpp>
#include <jln/mp/smp/algorithm/replace.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/functional/flip.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/list/push_back.hpp>
#include <jln/mp/smp/list/push_front.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using min = fold<if_<
    contract<mp::flip<concepts::predicate<assume_binary<Cmp>>>>,
    contract<mp::at1<>>,
    contract<mp::at0<>>
  >, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<contract<mp::size<>>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold<if_<
    contract<concepts::predicate<assume_binary<Cmp>>>,
    contract<mp::at1<>>,
    contract<mp::at0<>>
  >, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<contract<mp::size<>>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = detail::sfinae<mp::clamp<Min, Max, subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = tee<identity, neg<>, if_<Cmp,
    contract<mp::at1<subcontract<C>>>,
    contract<mp::at0<subcontract<C>>>
  >>;


  template<class C = identity>
  using pow = try_contract<pow<subcontract<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, lift<_pow, C>>
  {
    using type = smp::pow<sfinae<C>>;
  };
}
/// \endcond
