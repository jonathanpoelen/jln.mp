// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/mismatch.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/select.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Returns the first mismatching index of elements from two sequences, otherwise the size of the sequences.
  /// \treturn \number
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<Cmp, front<C>, reverse_select<front<is<number<-1>>>, C>>;

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::identity>
    using mismatch_index = typename mismatch_index<Cmp, C>::template f<seq1, seq2>;

    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::identity>
    constexpr bool mismatch_index_v = mismatch_index<Cmp, C>::template f<seq1, seq2>::value;
  }
}
