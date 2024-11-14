// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/partial_each.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the second element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_second = partial_each<identity, F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_second = typename detail::_unpack<mp::partial_each<mp::identity, F, C>, L>::type;
  }
}
