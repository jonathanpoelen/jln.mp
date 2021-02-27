#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop.hpp>
#include <jln/mp/list/take.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// \pre `0 <= i < sizeof...(xs)`
  /// \pre seq must be a \list
  /// \treturn \sequence
  template<class i, class seq, class C = listify>
  using insert_range = tee<take<i>, always<seq>, drop<i>, join<C>>;

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
