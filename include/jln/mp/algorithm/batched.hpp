// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/sliding.hpp>


namespace jln::mp
{
  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `size <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   batched_c<2>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<int_ size, class F = listify, class C = listify>
  using batched_with_c = strided_sliding_with_c<size, size, F, C>;

  template<int_ size, class C = listify>
  using batched_c = strided_sliding_with_c<size, size, listify, C>;

  template<class size, class F = listify, class C = listify>
  using batched_with = strided_sliding_with_c<size::value, size::value, F, C>;

  template<class size, class C = listify>
  using batched = strided_sliding_with_c<size::value, size::value, listify, C>;

  namespace emp
  {
    template<class L, class size, class F = mp::listify, class C = mp::listify>
    using batched_with = unpack<L, mp::strided_sliding_with_c<size::value, size::value, F, C>>;

    template<class L, int_ size, class F = mp::listify, class C = mp::listify>
    using batched_with_c = unpack<L, mp::strided_sliding_with_c<size, size, F, C>>;

    template<class L, class size, class C = mp::listify>
    using batched = unpack<L, mp::strided_sliding_with_c<size::value, size::value, mp::listify, C>>;

    template<class L, int_ size, class C = mp::listify>
    using batched_c = unpack<L, mp::strided_sliding_with_c<size, size, mp::listify, C>>;
  }
}
