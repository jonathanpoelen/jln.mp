// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/pairwise_fold.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/functional/select.hpp>


namespace jln::mp
{
  /// \ingroup filter

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  using remove_adjacent_if = pairwise_fold_and_transform_front<
    select<BinaryPred, always<list<>>, listify>,
    listify,
    join<C>
  >;

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using remove_adjacent_if = typename detail::_unpack<mp::remove_adjacent_if<BinaryPred, C>, L>::type;

    template<class L, class C = mp::listify>
    using remove_adjacent = typename detail::_unpack<mp::remove_adjacent<C>, L>::type;
  }
}
