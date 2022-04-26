#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/algorithm/lower_bound.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class x, class Cmp, class TC, class FC>
  struct _smp_lower_bound_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class x, class Cmp, class TC = listify, class FC = TC>
  using lower_bound = contract<detail::_smp_lower_bound_impl<
    x, concepts::strong_predicate_or<assume_binary<Cmp>, violation>,
    subcontract<TC>, subcontract<FC>>>;

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using lower_bound_c = lower_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using lower_bound_than = lower_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using lower_bound_than_c = lower_bound<number<x>, less<>, TC, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class Cmp, class TC, class FC>
  struct _sfinae<sfinae, lower_bound<x, Cmp, TC, FC>>
  {
    using type = smp::lower_bound<x, sfinae<Cmp>, sfinae<TC>, sfinae<FC>>;
  };

  template<class x, class Cmp, class C, class FC>
  struct _smp_lower_bound_impl
  {
    template<class... xs>
    using f = typename detail::_smp_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<sizeof...(xs), push_back<x, Cmp>, C, FC, xs...>;
  };
}
/// \endcond
