// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes the last element of sequence.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \sequence
  template<class C = listify>
  using pop_back = rotate_c<-1, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = typename detail::_unpack<mp::pop_back<C>, L>::type;
  }
}
