#pragma once

#include "../concepts.hpp"
#include "../list/list.hpp"
#include "../utility/same_as.hpp"
#include "../number/operators.hpp"
#include "../functional/identity.hpp"
#include "../../list/front.hpp"
#include "../../algorithm/lower_bound.hpp"

namespace jln::mp::detail
{
  template<class x, class Cmp, class C, class NC>
  struct _smp_lower_bound_impl;
}

namespace jln::mp::smp
{
  template<class x, class Cmp, class C = listify, class NC = C>
  using lower_bound = contract<detail::_smp_lower_bound_impl<
    x, subcontract<Cmp>, subcontract<C>, subcontract<NC>>>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using lower_bound_of = lower_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_of_c = lower_bound<number<x>, less<>, C, NC>;
}

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
