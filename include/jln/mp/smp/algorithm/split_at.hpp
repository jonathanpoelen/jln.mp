#pragma once

#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/split_at.hpp"

namespace jln::mp::smp
{
  template<class i, class C = listify>
  using split_at = try_contract<mp::split_at<i, subcontract<C>>>;

  template<int_ i, class C = listify>
  using split_at_c = split_at<number<i>, C>;
}
