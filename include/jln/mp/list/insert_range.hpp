#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Inserts all elements of \c seq at an arbitrary position.
  /// \pre `0 <= i < sizeof...(xs)`
  /// \pre seq must be a \list
  /// \treturn \sequence
  template<unsigned i, class seq, class C = listify>
  using insert_range_c = tee<take_front_c<i>, always<seq>, drop_front_c<i>, join<C>>;

  template<class i, class seq, class C = listify>
  using insert_range = insert_range_c<i::value, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using insert_range = unpack<L, mp::insert_range<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using insert_range_c = unpack<L, mp::insert_range_c<i, seq, C>>;
  }
}
