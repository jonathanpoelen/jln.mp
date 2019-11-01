#pragma once

#include "../algorithm/rotate.hpp"
#include "pop_front.hpp"
#include "../../list/pop_back.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using pop_back = mp::detail::sfinae<mp::pop_back<subcontract<C>>>;
}
