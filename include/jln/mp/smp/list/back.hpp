#pragma once

#include "../algorithm/rotate.hpp"
#include "front.hpp"
#include "../../list/back.hpp"

namespace jln::mp::smp
{
  template<class C = identity>
  using back = mp::detail::sfinae<mp::back<assume_unary<C>>>;
}
