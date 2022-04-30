#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/list.hpp>
#include <utility>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class F, class Ints>
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
    using f = typename detail::circulant_matrix_impl<F, std::make_index_sequence<sizeof...(xs)>>
      ::template f<C>
      ::template f<xs...>;
  };

  template<class C = listify>
  using circulant_matrix = circulant_matrix_with<listify, C>;

  namespace emp
  {
    template<class L, class F, class C = mp::listify>
    using circulant_matrix_with = unpack<L, mp::circulant_matrix_with<F, C>>;

    template<class L, class C = mp::listify>
    using circulant_matrix = unpack<L, mp::circulant_matrix<C>>;
  }
}

#include <jln/mp/functional/tee.hpp>
#include <jln/mp/algorithm/rotate.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F, std::size_t... i>
  struct circulant_matrix_impl<F, std::integer_sequence<std::size_t, i...>>
  {
    template<class C>
    using f = _tee<C, rotate_c<-int_(i), F>...>;
  };
}
/// \endcond
