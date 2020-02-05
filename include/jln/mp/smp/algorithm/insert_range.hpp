#pragma once

#include "../list/join.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"
#include "../../algorithm/insert_range.hpp"

namespace jln::mp::smp
{
  template<class i, class seq, class C = listify>
  using insert_range = detail::sfinae<mp::insert_range<i, seq, C>>;

  template<int_ i, class seq, class C = listify>
  using insert_range_c = insert_range<number<i>, seq, C>;
}
