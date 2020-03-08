#pragma once

#include "../algorithm/transform.hpp"
#include "../utility/unpack.hpp"
#include "../../functional/cascade.hpp"

namespace jln::mp::smp
{
  template<class F, class... Fs>
  using cascade = typename detail::sfinae<mp::cascade<
    subcontract_barrier<F>,
    subcontract_barrier<Fs>...
  >>;
}
