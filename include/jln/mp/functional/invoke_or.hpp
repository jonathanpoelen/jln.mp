#pragma once

#include "if.hpp"
#include "is_invovable.hpp"

namespace jln::mp
{
  template<class continuation = identity, class or_continuation = identity>
  using invoke_or = if_<is_invocable<continuation>, continuation, or_continuation>;
} // namespace jln::mp
