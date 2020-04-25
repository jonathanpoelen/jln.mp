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
  using min = fold_left<if_<contract<mp::flip<assume_binary<Cmp>>>, contract<mp::at1<>>, contract<mp::at0<>>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<contract<mp::size<>>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold_left<if_<Cmp, contract<mp::at1<>>, contract<mp::at0<>>>, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<contract<mp::size<>>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = detail::sfinae<mp::clamp<Min, Max, subcontract_barrier<Cmp>, subcontract_barrier<C>>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = detail::sfinae<mp::abs<subcontract_barrier<Cmp>, subcontract_barrier<C>>>;


  template<class C = identity>
  using pow = detail::sfinae<mp::pow<subcontract_barrier<C>>>;

  template<class C = identity>
  using pow0 = if_<contract<mp::size<>>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<contract<mp::size<>>, pow<C>, always<number<1>, C>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae>
  struct _sfinae<sfinae, _pow>
  {
    using type = try_contract<_pow>;
  };
}
/// \endcond
