#pragma once

#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/list/back.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using back = mp::detail::sfinae<mp::back<assume_unary<C>>>;
}
