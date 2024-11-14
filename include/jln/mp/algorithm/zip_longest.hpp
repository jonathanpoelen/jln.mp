// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/zip.hpp>
#include <jln/mp/algorithm/matrix_longest.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Turns rows into columns, and columns into rows.
  /// Missing values are filled-in with fillvalue.
  /// This is similar to transposing a matrix.
  /// \semantics
  ///   \code
  ///   zip_longest<_0>::f<
  ///     list<_1, _2, _3>,
  ///     list<_a, _b, _c, _d>
  ///   > = list<
  ///     list<_1, _a>,
  ///     list<_2, _b>,
  ///     list<_3, _c>
  ///     list<_0, _d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see zip
  template<class FillValue, class C = listify>
  using zip_longest = right_matrix_longest<FillValue, zip<C>>;

  template<class FillValue, class F = listify, class C = listify>
  using zip_longest_with = right_matrix_longest<FillValue, zip_with<F, C>>;

  namespace emp
  {
    template<class L, class FillValue, class C = mp::listify>
    using zip_longest = typename detail::_unpack<mp::zip_longest<FillValue, C>, L>::type;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using zip_longest_with = typename detail::_unpack<mp::zip_longest_with<FillValue, F, C>, L>::type;
  }
}
