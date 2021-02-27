#pragma once

#include <jln/mp/list/drop.hpp>
#include <jln/mp/list/take.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \values
  template<class i, class F = listify, class C = listify>
  using split_at_with = tee<take<i, F>, drop<i, F>, C>;

  template<int_ i, class F = listify, class C = listify>
  using split_at_with_c = split_at_with<number<i>, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \lists
  template<class i, class C = listify>
  using split_at = tee<take<i>, drop<i>, C>;

  template<int_ i, class C = listify>
  using split_at_c = split_at<number<i>, C>;

  namespace emp
  {
    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at_with<i, F, C>>;

    template<class L, int_ i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at_with_c<i, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at<i, C>>;

    template<class L, int_ i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at_c<i, C>>;
  }
}
