#pragma once

#include "identity.hpp"
#include "../../functional/is_invocable.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using is_invocable = contract<mp::is_invocable<subcontract<F>, subcontract<C>>>;
}
