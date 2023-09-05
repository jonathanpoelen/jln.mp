// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, class F>
    struct anticirculant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the left relative to the preceding row vector.
  /// \semantics
  ///   \code
  ///   anticirculant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<b, c, d, a>,
  ///     list<c, d, a, b>,
  ///     list<d, a, b, c>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see circulant_matrix
  template<class F = listify, class C = listify>
  struct anticirculant_matrix_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(xs), detail::anticirculant_matrix_impl<C, F>::template f
    )::template f<xs...>;
  };

  template<class C = listify>
  using anticirculant_matrix = anticirculant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using anticirculant_matrix_with = unpack<L, mp::anticirculant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using anticirculant_matrix = unpack<L, mp::anticirculant_matrix<C>>;
  }
}

#include <jln/mp/functional/tee.hpp>
#include <jln/mp/algorithm/rotate.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, class F>
  struct anticirculant_matrix_impl
  {
    template<class, int_... i>
    using f = _tee<C, rotate_c<i, F>...>;
  };
}
/// \endcond
