#pragma once

#include "make_int_sequence.hpp"
#include "../list/size.hpp"
#include "../../algorithm/indices.hpp"

namespace jln::mp::smp
{
  template<class C = listify>
  using indices = contract<mp::indices<subcontract<C>>>;
}
