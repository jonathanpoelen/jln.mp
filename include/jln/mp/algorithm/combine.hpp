// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/product.hpp>
#include <jln/mp/algorithm/repeat.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Computes all possible combinations (with repetition) from the elements in a \sequence.
  /// \treturn \sequence of \list
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename detail::repeat_impl<1, sizeof...(xs), product<C>>
      ::template f<list<xs...>>::type;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = typename detail::_unpack<mp::combine<C>, L>::type;
  }
}
