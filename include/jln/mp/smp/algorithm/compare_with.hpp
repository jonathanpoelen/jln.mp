#pragma once

#include "../functional/each.hpp"
#include "../number/operators.hpp"
#include "../../algorithm/compare_with.hpp"


namespace jln::mp::smp
{
  template<class F, class Cmp = less<>>
  using compare_with = each<F, F, Cmp>;
}
