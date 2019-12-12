#pragma once

#include "../../number/math.hpp"
#include "../number/operators.hpp"
#include "../algorithm/fold_left.hpp"
#include "../functional/fork.hpp"
#include "../functional/flip.hpp"
#include "../functional/if.hpp"
#include "../list/drop.hpp"
#include "../list/front.hpp"
#include "../list/push_back.hpp"
#include "../list/push_front.hpp"

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using min = mp::detail::sfinae<mp::min<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class Cmp = less<>, class C = identity>
  using min0 = mp::detail::sfinae<mp::min0<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class Cmp = less<>, class C = identity>
  using max = mp::detail::sfinae<mp::max<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class Cmp = less<>, class C = identity>
  using max0 = mp::detail::sfinae<mp::max0<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = mp::detail::sfinae<mp::clamp<Min, Max, subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = mp::detail::sfinae<mp::clamp_c<min, max, subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class Cmp = less<>, class C = identity>
  using abs = mp::detail::sfinae<mp::abs<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<class C = identity>
  using pow = mp::detail::sfinae<mp::pow<subcontract_barrier<C>>>;

  template<class C = identity>
  using pow0 = mp::detail::sfinae<mp::pow0<subcontract_barrier<C>>>;

  template<class C = identity>
  using pow1 = mp::detail::sfinae<mp::pow1<subcontract_barrier<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, _pow>
  {
    using type = try_contract<_pow>;
  };
}
