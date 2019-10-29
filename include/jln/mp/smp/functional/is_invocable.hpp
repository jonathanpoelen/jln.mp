#pragma once

#include "identity.hpp"
#include "../../functional/is_invocable.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using is_invocable = valid_contract<try_invoke<F,
    mp::always<mp::call<mp::try_invoke<subcontract<C>>, true_>>,
    mp::always<mp::call<mp::try_invoke<subcontract<C>>, false_>>
  >>;
}
