// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/partial_transform.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the third element of the \sequence.
  /// \treturn \list
  template<class F, class C = listify>
  using transform_third = partial_transform<identity, identity, F, C>;

  namespace emp
  {
    template<class L, class F, class C = listify>
    using transform_third = typename detail::_unpack<mp::partial_transform<mp::identity, mp::identity, F, C>, L>::type;
  }
}
