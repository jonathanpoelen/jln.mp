#pragma once

#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/insert.hpp"

namespace jln::mp::smp
{
  template<class i, class seq, class C = listify>
  using insert = try_contract<mp::insert<i, seq, subcontract<C>>>;

  template<int_ i, class seq, class C = listify>
  using insert_c = insert<number<i>, seq, C>;
}
