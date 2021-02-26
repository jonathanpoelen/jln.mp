#pragma once

#include "mismatch.hpp"
#include "../list/at.hpp"
#include "../utility/always.hpp"
#include "../utility/is.hpp"
#include "../functional/lift.hpp"
#include "../functional/identity.hpp"
#include "../functional/invoke_twice.hpp"

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
    using mismatch_index = call<mismatch_index<Cmp, C>, seq1, seq2>;
  }
}
