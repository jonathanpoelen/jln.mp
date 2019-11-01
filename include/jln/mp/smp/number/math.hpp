#pragma once

#include "../../number/math.hpp"
#include "../number/operators.hpp"
#include "../algorithm/fold_left.hpp"
#include "../functional/fork.hpp"
#include "../functional/flip.hpp"
#include "../functional/if.hpp"
#include "../list/drop.hpp"
#include "../list/front.hpp"

namespace jln::mp::smp
{
  template<class Pred = less<>, class C = identity>
  using min = mp::detail::sfinae<mp::min<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using min0 = mp::detail::sfinae<mp::min0<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using max = mp::detail::sfinae<mp::max<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using max0 = mp::detail::sfinae<mp::max0<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using abs = mp::detail::sfinae<mp::abs<subcontract<Pred>, subcontract<C>>>;

  template<class C = identity>
  using pow = mp::detail::sfinae<mp::pow<subcontract<C>>>;

  template<class C = identity>
  using pow0 = mp::detail::sfinae<mp::pow0<subcontract<C>>>;

  template<class C = identity>
  using pow1 = mp::detail::sfinae<mp::pow1<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, _pow>
  {
    using type = try_contract<_pow>;
  };
}
