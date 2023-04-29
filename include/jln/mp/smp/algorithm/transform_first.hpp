#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/partial_each.hpp>
#include <jln/mp/algorithm/transform_first.hpp>

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform_first = detail::_smp_partial_each::f<C, F>;
}
