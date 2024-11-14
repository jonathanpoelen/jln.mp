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
    struct circulant_matrix_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// square matrix in which all row vectors are composed of the
  /// same elements and each row vector is rotated one element to
  /// the right relative to the preceding row vector.
  /// \semantics
  ///   \code
  ///   circulant_matrix_with<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b, c, d>,
  ///     list<d, a, b, c>,
  ///     list<c, d, a, b>,
  ///     list<b, c, d, a>
  ///   >
  ///   \endcode
  /// \treturn \value
  /// \see anticirculant_matrix
  template<class F = listify, class C = listify>
  struct circulant_matrix_with
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(
      sizeof...(xs), detail::circulant_matrix_impl<C, F>::template impl
    )::template f<xs...>;
  };

  template<class C = listify>
  using circulant_matrix = circulant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using circulant_matrix_with = typename detail::_unpack<mp::circulant_matrix_with<F, C>, L>::type;

    template<class L, class C = mp::listify>
    using circulant_matrix = typename detail::_unpack<mp::circulant_matrix<C>, L>::type;
  }
}

#include <jln/mp/functional/tee.hpp>
#include <jln/mp/algorithm/rotate.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, class F>
  struct circulant_matrix_impl
  {
    template<class, int_... i>
    struct impl : _tee<C, rotate_c<-i, F>...>
    {};
  };
}
/// \endcond
