// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/number/not.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Checks whether a sequence has elements.
  /// \treturn \bool
  template<class C = identity>
  using is_not_empty = size<is<number<0>, not_<C>>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_not_empty = unpack<L, mp::is_not_empty<C>>;
  }
}
