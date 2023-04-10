#pragma once

#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/map/map_keys.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using map_keys = detail::sfinae<mp::map_keys<subcontract<C>>>;

  template<class F = identity, class C = listify>
  using map_keys_with = detail::sfinae<mp::map_keys_with<assume_unary<F>, subcontract<C>>>;
}
