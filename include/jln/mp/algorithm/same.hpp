// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/expr_to_bool.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/algorithm/same_xs.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether all \values are identical.
  /// \treturn \bool
  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::same_xs_v<xs...>>);
  };

  template<class C = identity>
  struct same_v
  {
    template<class... xs>
    using f = typename C::template f<emp::same_xs_v<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;

    template<class L, class C = mp::identity>
    inline constexpr bool same_v = unpack<L, mp::same<C>>::value;
  }
}


/// \cond
namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = number<emp::same_xs_v<xs...>>;
  };
}
/// \endcond
