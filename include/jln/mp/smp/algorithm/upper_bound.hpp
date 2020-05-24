#pragma once

#include "lower_bound.hpp"
#include "../functional/tee.hpp"
#include "../functional/flip.hpp"
#include "../../algorithm/upper_bound.hpp"

namespace jln::mp::smp
{
  template<class x, class Cmp, class C = listify, class NC = C>
  using upper_bound = contract<detail::_smp_lower_bound_impl<
    x, mp::flip<
      subcontract<tee<try_assume_binary<Cmp>, not_<>>>>,
      subcontract<C>, subcontract<NC>
    >
  >;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound_c = upper_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using upper_bound_than = upper_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_than_c = upper_bound<number<x>, less<>, C, NC>;
}
