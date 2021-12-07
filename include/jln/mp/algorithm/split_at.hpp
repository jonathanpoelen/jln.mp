#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/functional/tee.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \values
  template<unsigned i, class F = listify, class C = listify>
  using split_at_with_c = tee<take_front_c<i, F>, drop_front_c<i, F>, C>;

  template<class i, class F = listify, class C = listify>
  using split_at_with = split_at_with_c<i::value, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre i >= 0 && i <= sizeof...(xs)
  /// \treturn \sequence of two \lists
  template<unsigned i, class C = listify>
  using split_at_c = tee<take_front_c<i>, drop_front_c<i>, C>;

  template<class i, class C = listify>
  using split_at = split_at_c<i::value, C>;

  namespace emp
  {
    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at_with<i, F, C>>;

    template<class L, unsigned i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at_with_c<i, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at<i, C>>;

    template<class L, unsigned i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at_c<i, C>>;
  }
}
