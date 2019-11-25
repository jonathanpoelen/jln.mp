#pragma once

#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/splice.hpp"

namespace jln::mp::smp
{
  template<class i, class seq, class C = listify>
  using splice = try_contract<mp::splice<i, seq, subcontract<C>>>;

  template<int_ i, class seq, class C = listify>
  using splice_c = splice<number<i>, seq, C>;
}
