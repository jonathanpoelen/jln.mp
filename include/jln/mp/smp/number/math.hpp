#pragma once

#include "../../number/math.hpp"
#include "../number/operators.hpp"

namespace jln::mp::smp
{
  template<class Pred = less<>, class C = identity>
  using min = mp::sfinae<mp::min<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using min0 = mp::sfinae<mp::min0<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using max = mp::sfinae<mp::max<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using max0 = mp::sfinae<mp::max0<subcontract<Pred>, subcontract<C>>>;

  template<class Pred = less<>, class C = identity>
  using abs = mp::sfinae<mp::abs<subcontract<Pred>, subcontract<C>>>;

  template<class C = identity>
  using pow = mp::sfinae<mp::pow<subcontract<C>>>;

  template<class C = identity>
  using pow0 = mp::sfinae<mp::pow0<subcontract<C>>>;

  template<class C = identity>
  using pow1 = mp::sfinae<mp::pow1<subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, _pow>
  {
    using type = try_contract<_pow>;
  };
}
