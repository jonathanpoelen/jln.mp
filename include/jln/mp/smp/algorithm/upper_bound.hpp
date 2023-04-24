#pragma once

#include <jln/mp/smp/algorithm/lower_bound.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/functional/flip.hpp>
#include <jln/mp/algorithm/upper_bound.hpp>

namespace jln::mp::smp
{
  template<class x, class Cmp, class TC = listify, class FC = TC>
  using upper_bound = contract<detail::_smp_lower_bound_impl<
    x, mp::flip<concepts::predicate<assume_binary<Cmp>, mp::not_<>, violation>>,
    subcontract<TC>, subcontract<FC>
  >>;

  template<int_ x, class Cmp = less<>, class TC = listify, class FC = TC>
  using upper_bound_c = upper_bound<number<x>, Cmp, TC, FC>;

  template<class x, class TC = listify, class FC = TC>
  using upper_bound_than = upper_bound<x, less<>, TC, FC>;

  template<int_ x, class TC = listify, class FC = TC>
  using upper_bound_than_c = upper_bound<number<x>, less<>, TC, FC>;
}
