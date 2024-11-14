// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/algorithm/transform.hpp>

namespace jln::mp
{
  /// \ingroup filter

  /// Copies all elements that satisfy a predicate.
  /// \treturn \sequence
  template<class Pred, class C = listify>
  using copy_if = transform<wrap_in_list_if<Pred>, join<C>>;

  /// Copies all occurence of a \value.
  /// \treturn \sequence
  template<class x, class C = listify>
  using copy = copy_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = typename detail::_unpack<mp::copy_if<Pred, C>, L>::type;

    template<class L, class x, class C = mp::listify>
    using copy = typename detail::_unpack<mp::copy<x, C>, L>::type;
  }
}
