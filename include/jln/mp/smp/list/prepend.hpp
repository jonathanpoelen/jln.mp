#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/list/push_front.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/list/prepend.hpp>

namespace jln::mp::smp
{
  template<class L, class C = listify>
  using prepend = contract<mp::push_front<L, subcontract<unpack<C>>>>;
}
