#pragma once

#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../utility/always.hpp"
#include "../functional/fork.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Insert all elements of \c seq at an arbitrary position.
  /// \pre 0 \<= i \< sizeof...(xs)
  /// \pre seq must be a \list
  /// \return \sequence
  template<class i, class seq, class C = listify>
  using insert_range = fork<take<i>, always<seq>, drop<i>, join<C>>;

  template<int_ i, class seq, class C = listify>
  using insert_range_c = insert_range<number<i>, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using insert_range = unpack<L, mp::insert_range<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using insert_range_c = unpack<L, mp::insert_range_c<i, seq, C>>;
  }
}
