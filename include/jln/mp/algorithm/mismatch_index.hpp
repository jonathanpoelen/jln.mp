// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/mismatch.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Returns the first mismatching index of elements from two sequences, otherwise the size of the sequences.
  /// \treturn \number
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<Cmp, at0<C>, if_<at0<is<number<-1>>>, at1<C>, at0<C>>>;

  namespace emp
  {
    template<class seq1, class seq2, class Cmp = mp::equal<>, class C = mp::identity>
    using mismatch_index = typename mismatch_index<Cmp, C>::template f<seq1, seq2>;
  }
}
