// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/repeat.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/functional/bind_back.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class FillValue, class F, class EvenSizeF, class C, int_t max, class... ns>
    using matrix_longest_each_impl = _each<
      C,
      JLN_MP_CONDITIONAL_C_T(
        max != ns::value,
        JLN_MP_REPEAT_VALUE_T(F, max - ns::value, FillValue),
        EvenSizeF
      )
    ...>;

    constexpr int_t max_lengths();

    template<class... Ts>
    constexpr int_t max_lengths(int_t r, Ts... len);

    template<class FillValue, class F, class EvenSizeF, class C, class... ns>
    using matrix_longest_impl = matrix_longest_each_impl<
      FillValue, F, EvenSizeF, C, max_lengths(ns::value...), ns...>;
  }
  /// \endcond

  /// \ingroup group

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<XX, XX, _1, _2>,
  ///     list<XX, _1, _2, _3>,
  ///     list<XX, XX, _1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct left_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack<F>, cfe<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, typename detail::_unpack<size<>, seqs>::type...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using left_matrix_longest = left_matrix_longest_with<FillValue, listify, C>;

  /// Fills a \sequence of \typelist to the longest size.
  /// \post `emp::size<result> == emp::max<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_longest_with_matrix_longest_with<XX, listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, XX>,
  ///     list<_1, _2, XX, XX>,
  ///     list<_1, _2, _3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class FillValue, class F = listify, class C = listify>
  struct right_matrix_longest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_longest_impl<
      FillValue,
      push_front<unpack_append<F>, cfe<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, typename detail::_unpack<size<>, seqs>::type...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using right_matrix_longest = right_matrix_longest_with<FillValue, listify, C>;

  namespace emp
  {
    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using left_matrix_longest_with = typename detail::_unpack<mp::left_matrix_longest_with<FillValue, F, C>, L>::type;

    template<class L, class FillValue, class C = mp::listify>
    using left_matrix_longest = typename detail::_unpack<mp::left_matrix_longest<FillValue, C>, L>::type;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using right_matrix_longest_with = typename detail::_unpack<mp::right_matrix_longest_with<FillValue, F, C>, L>::type;

    template<class L, class FillValue, class C = mp::listify>
    using right_matrix_longest = typename detail::_unpack<mp::right_matrix_longest<FillValue, C>, L>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_t max_lengths()
  {
    return 0;
  }

  template<class... Ts>
  constexpr int_t max_lengths(int_t r, Ts... len)
  {
    (..., ((len > r) ? void(r = len) : void()));
    return r;
  }
}
/// \endcond
