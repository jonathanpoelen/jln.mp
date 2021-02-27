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
  template<class x, class Cmp, class C, class NC>
  struct _smp_lower_bound_impl;
}
/// \endcond

namespace jln::mp::smp
{
  template<class x, class Cmp, class C = listify, class NC = C>
  using lower_bound = contract<detail::_smp_lower_bound_impl<
    x, subcontract<Cmp>, subcontract<C>, subcontract<NC>>>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using lower_bound_than = lower_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_than_c = lower_bound<number<x>, less<>, C, NC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class x, class Cmp, class C, class NC>
  struct _sfinae<sfinae, lower_bound<x, Cmp, C, NC>>
  {
    using type = smp::lower_bound<x, sfinae<Cmp>, sfinae<C>, sfinae<NC>>;
  };

  template<class x, class Cmp, class C = listify, class NC = C>
  struct _smp_lower_bound_impl
  {
    template<class... xs>
    using f = typename detail::_smp_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<sizeof...(xs), push_back<x, Cmp>, C, NC, xs...>;
  };
}
/// \endcond
