#pragma once

#include "../list/list.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack_append.hpp"
#include "../../algorithm/append.hpp"

namespace jln::mp::smp
{
  template<class L, class C = listify>
  using append = valid_contract<mp::push_front<L, subcontract<unpack_append<C>>>>;
}
