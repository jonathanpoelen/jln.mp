#pragma once

#include "../algorithm/transform.hpp"
#include "../functional/bind.hpp"
#include "../utility/unpack.hpp"
#include "../../functional/cascade.hpp"

namespace jln::mp::smp
{
  template<class F, class... Fs>
  using cascade = typename detail::sfinae<mp::cascade<
    contract_barrier<subcontract<F>>,
    contract_barrier<subcontract<Fs>>...
  >>;
}
