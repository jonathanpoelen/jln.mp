#pragma once

#include <jln/mp/algorithm/fold_left.hpp>
#include <jln/mp/algorithm/zip.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct counter_inc;
    struct counter_push;
    struct counter_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Counts all distinct elements and returns a list of pairs containing
  /// the repeat count and the type.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   call<counter<>, int, int, char, double, int, double>
  ///   == list<
  ///     list<number<3>, int>,
  ///     list<number<1>, char>,
  ///     list<number<2>, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of \number and type
  template<class C = listify>
  struct counter : push_front<list<list<>, list<>>, fold_left<detail::counter_impl, unpack<zip<C>>>>
  {
  #ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
  #endif
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using counter = unpack<L, mp::counter<C>>;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  struct counter_inc_first
  {
    template<class n, class... ns>
    using f = list<number<n::value + 1>, ns...>;
  };

  struct counter_inc
  {
    template<class I>
    struct f
    {
      template<class x, class... xs>
      using elements = list<xs...>;

      template<class... ints>
      using indexes = typename _join_select<2>::f<
        listify,
        typename take_front<I>::template f<ints...>,
        typename drop_front<I, counter_inc_first>::template f<ints...>
      >::type;
    };
  };

  struct counter_push
  {
    template<class x, class... xs>
    using elements = list<xs..., x>;

    template<class... ints>
    using indexes = list<ints..., number<1>>;
  };

  template<class>
  struct counter_next;

  template<class... xs, class... ints>
  struct counter_next<list<list<ints...>, list<xs...>>>
  {
    template<class M, class x>
    using next = list<
      typename M::template indexes<ints...>,
      typename M::template elements<x, xs...>
    >;

    template<class x>
    using f = next<
      typename index_if<is<x>, detail::counter_inc, always<detail::counter_push>>
      ::template f<xs...>,
      x
    >;
  };

  struct counter_impl
  {
    template<class L, class x>
    using f = typename counter_next<L>::template f<x>;
  };
}
/// \endcond
