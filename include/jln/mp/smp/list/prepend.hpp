#pragma once

#include "../list/listify.hpp"
#include "../list/push_front.hpp"
#include "../utility/unpack.hpp"
#include "../../list/prepend.hpp"

namespace jln::mp::smp
{
  template<class L, class C = listify>
  using prepend = contract<mp::push_front<L, subcontract<unpack<C>>>>;
}