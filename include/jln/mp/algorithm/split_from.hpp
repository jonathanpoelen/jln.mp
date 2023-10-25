// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split_at.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence at an arbitrary position returns by \c GetIndex.
  /// \pre `GetIndex::f<xs...>::value >= 0 && GetIndex::f<xs...>::value <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_from2
  {
    template<class... xs>
    using f = typename detail::split_at_impl<
      JLN_MP_DCALL_V_TRACE_XS(xs, GetIndex, xs...)::value, SubC1, SubC2, C, xs...>;
  };

  template<class GetIndex, class C = listify>
  using split_from = split_from2<GetIndex, listify, listify, C>;

  namespace emp
  {
    template<class L, class GetIndex,
      class SubC1 = mp::listify, class SubC2 = SubC1, class C = mp::listify>
    using split_from2 = unpack<L, mp::split_from2<GetIndex, SubC1, SubC2, C>>;

    template<class L, class GetIndex, class C = mp::listify>
    using split_from = unpack<L, mp::split_from2<GetIndex, mp::listify, mp::listify, C>>;
  }
}
