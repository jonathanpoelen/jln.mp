#pragma once

#include <jln/mp/algorithm/repeat.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/bind_back.hpp>
#include <initializer_list>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class FillValue, class F, class EvenSizeF, class C, int_ max, class... ns>
    using matrix_longest_each_impl = _each<
      C,
      typename conditional_c<max != ns::value>
      ::template f<
        typename repeat_c<max - ns::value, F>::template f<FillValue>,
        EvenSizeF
      >
    ...>;

    constexpr int_ max_lengths(std::initializer_list<int_> l);

    template<class FillValue, class F, class EvenSizeF, class C, class... ns>
    using matrix_longest_impl = matrix_longest_each_impl<
      FillValue, F, EvenSizeF, C, max_lengths({ns::value...}), ns...>;
  }
  /// \endcond

  /// \ingroup algorithm

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
      push_front<unpack<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
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
      push_front<unpack_append<F>, lift<bind_back>>,
      typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class FillValue, class C = listify>
  using right_matrix_longest = right_matrix_longest_with<FillValue, listify, C>;

  namespace emp
  {
    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using left_matrix_longest_with = unpack<L, mp::left_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using left_matrix_longest = unpack<L, mp::left_matrix_longest<FillValue, C>>;

    template<class L, class FillValue, class F = mp::listify, class C = mp::listify>
    using right_matrix_longest_with = unpack<L, mp::right_matrix_longest_with<FillValue, F, C>>;

    template<class L, class FillValue, class C = mp::listify>
    using right_matrix_longest = unpack<L, mp::right_matrix_longest<FillValue, C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ max_lengths(std::initializer_list<int_> l)
  {
    int_ r = 0;
    for (int_ n : l) {
      if (n > r) {
        r = n;
      }
    }
    return r;
  }
}
/// \endcond