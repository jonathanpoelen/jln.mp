// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned position, class C1, class C2, class C, class... xs>
    using split_at_impl = typename C::template f<
      // take_front
      typename detail::rotate_impl<position>
      ::template f<position, drop_front_c<sizeof...(xs) - position, C1>, xs...>,
      typename drop_front_c<position, C2>::template f<xs...>
    >;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<unsigned i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_at2_with_c
  {
    template<class... xs>
    using f = typename detail::split_at_impl<(sizeof...(xs) & 0) + i, SubC1, SubC2, C, xs...>;
  };

  template<class i, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  using split_at2_with = split_at2_with_c<i::value, SubC1, SubC2, C>;

  template<unsigned i, class F = listify, class C = listify>
  using split_at_with_c = split_at2_with_c<i, F, F, C>;

  template<class i, class F = listify, class C = listify>
  using split_at_with = split_at2_with_c<i::value, F, F, C>;

  /// Splits a sequence at an arbitrary position.
  /// \pre `i >= 0 && i <= sizeof...(xs)`
  /// \treturn \sequence of two \lists
  template<unsigned i, class C = listify>
  using split_at_c = split_at2_with_c<i, listify, listify, C>;

  template<class i, class C = listify>
  using split_at = split_at2_with_c<i::value, listify, listify, C>;

  namespace emp
  {
    template<class L, class i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with = unpack<L, mp::split_at2_with_c<i::value, SubC1, SubC2, C>>;

    template<class L, unsigned i, class SubC1 = mp::listify, class SubC2 = mp::listify,
             class C = mp::listify>
    using split_at2_with_c = unpack<L, mp::split_at2_with_c<i, SubC1, SubC2, C>>;

    template<class L, class i, class F = mp::listify, class C = mp::listify>
    using split_at_with = unpack<L, mp::split_at2_with_c<i::value, F, F, C>>;

    template<class L, unsigned i, class F = mp::listify, class C = mp::listify>
    using split_at_with_c = unpack<L, mp::split_at2_with_c<i, F, F, C>>;

    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at2_with_c<i::value, listify, listify, C>>;

    template<class L, unsigned i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at2_with_c<i, listify, listify, C>>;
  }
}
