#pragma once

#include "list.hpp"
#include "drop.hpp"
#include "../../list/pop_front.hpp"
#include "../../functional/sfinaefwd.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using pop_front = mp::detail::sfinae<mp::pop_front<subcontract<C>>>;
}
