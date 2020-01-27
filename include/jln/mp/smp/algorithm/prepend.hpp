#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack.hpp"
#include "../../algorithm/prepend.hpp"

namespace jln::mp::smp
{
  template<class L, class C = listify>
  using prepend = valid_contract<mp::push_front<L, subcontract<unpack<C>>>>;
}
