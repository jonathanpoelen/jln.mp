#pragma once

#include "make_int_sequence.hpp"
#include "../list/size.hpp"
#include "../../algorithm/indices.hpp"

namespace jln::mp
{
  namespace smp
  {
    template<class C = listify>
    using indices = valid_contract<mp::indices<subcontract<C>>>;
  }
} // namespace jln::mp
