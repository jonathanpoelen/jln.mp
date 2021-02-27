#pragma once

#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/smp/list//pop_front.hpp>
#include <jln/mp/list/pop_back.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using pop_back = mp::detail::sfinae<mp::pop_back<subcontract<C>>>;
}
