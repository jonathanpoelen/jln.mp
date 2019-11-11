#pragma once

#include "transform.hpp"
#include "../functional/if.hpp"
#include "../utility/always.hpp"
#include "../../algorithm/replace_if.hpp"

namespace jln::mp::smp
{
  template<class Pred, class T, class C = listify>
  using replace_if = detail::sfinae<mp::replace_if<
    subcontract_barrier<Pred>, T, subcontract_barrier<C>>>;
}
