#pragma once

#include <jln/mp/list/size.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/functional/each.hpp>
#include <algorithm>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct _drop_back
    {
      template<class F, class G, int_ min, class n>
      using impl = typename conditional_c<min != n::value>
        ::template f<unpack<take_front_c<min, F>>, G>;

      template<class F, class G, class C, class... ns>
      using f = _each<C, impl<F, G, std::min({int_(~0u), ns::value...}), ns>...>;
    };
  }
  /// \endcond

  /// \ingroup algorithm

  /// Truncates a \sequence of \typelist on the smallest size.
  /// \pre `sizeof...(result) == sizeof...(xs)`
  /// \post `emp::size<result> == emp::min<emp::size<xs>> && ...`
  /// \semantics
  ///   \code
  ///   matrix_shortest_with<listify>::f<
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
  /// \note A truncated values becomes a \list
  template<class F = listify, class C = listify>
  struct matrix_shortest_with
  {
    template<class... seqs>
    using f = typename detail::_drop_back::f<
      F, typename detail::optimize_useless_unpack<unpack<F>>::type,
      C, unpack<size<>>::f<seqs>...
    >::template f<seqs...>;
  };

  template<class C = listify>
  using matrix_shortest = matrix_shortest_with<listify, C>;

  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using matrix_shortest_with = unpack<L, mp::matrix_shortest_with<F, C>>;

    template<class L, class C = mp::listify>
    using matrix_shortest = unpack<L, mp::matrix_shortest<C>>;
  }
}
