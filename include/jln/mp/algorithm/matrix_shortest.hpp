#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/take_back.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/each.hpp>
#include <initializer_list>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    constexpr int_ min_lengths(std::initializer_list<int_> l);

    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, int_ min, class... ns>
    using matrix_shortest_each_impl = _each<
      C,
      typename conditional_c<min != ns::value>
      ::template f<unpack<Take<min, F>>, EvenSizeF>
    ...>;

    template<
      template<unsigned, class> class Take,
      class F, class EvenSizeF, class C, class... ns>
    using matrix_shortest_impl = matrix_shortest_each_impl<
      Take, F, EvenSizeF, C, min_lengths({ns::value...}), ns...>;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   left_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>,
  ///     list<_1, _2>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct left_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_front_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using left_matrix_shortest = left_matrix_shortest_with<listify, C>;

  /// Truncates a \sequence of \typelist to the smallest size.
  /// \post `emp::size<result> == emp::min<emp::size<seqs>> && ...`
  /// \semantics
  ///   \code
  ///   right_matrix_shortest_with<listify>::f<
  ///     list<_1, _2>,
  ///     list<_1, _2, _3>,
  ///     list<_1, _2>,
  ///     list<_1, _2, _3, _4>
  ///   > = list<
  ///     list<_1, _2>,
  ///     list<_2, _3>,
  ///     list<_1, _2>,
  ///     list<_3, _4>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<class F = listify, class C = listify>
  struct right_matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::matrix_shortest_impl<
      take_back_c,
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using right_matrix_shortest = right_matrix_shortest_with<listify, C>;


  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using left_matrix_shortest_with = unpack<L, mp::left_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using left_matrix_shortest = unpack<L, mp::left_matrix_shortest<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using right_matrix_shortest_with = unpack<L, mp::right_matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using right_matrix_shortest = unpack<L, mp::right_matrix_shortest<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  constexpr int_ min_lengths(std::initializer_list<int_> l)
  {
    if (l.size()) {
      auto first = l.begin();
      auto last = l.end();

      int_ r = *first++;
      for (; first != last; ++first) {
        if (*first < r) {
          r = *first;
        }
      }

      return r;
    }

    return 0;
  }
}
/// \endcond
