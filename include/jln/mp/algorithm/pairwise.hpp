#pragma once

#include <jln/mp/algorithm/rotate.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct pairwise_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Returns successive overlapping pairs.
  /// \post If `sizeof...(xs) <= 1`, then the result sequence is empty
  /// \post If `sizeof...(xs) > 1`, then the number of 2-tuples is `sizeof...(xs) - 1`
  /// \semantics
  ///   \code
  ///   pairwise<>::f<a, b, c, d>
  ///   == list<
  ///     list<a, b>,
  ///     list<b, c>,
  ///     list<c, d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see sliding, group_n
  template<class F = listify, class C = listify>
  struct pairwise_with
  {
    template<class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, JLN_MP_TRACE_F(F), xs...>
      ;
  };

  template<class C = listify>
  using pairwise = pairwise_with<listify, C>;

  namespace emp
  {
    template<class L, class F = mp::listify, class C = mp::listify>
    using pairwise_with = unpack<L, mp::pairwise_with<F, C>>;

    template<class L, class C = mp::listify>
    using pairwise = unpack<L, mp::pairwise<C>>;
  }
}

namespace jln::mp::detail
{
  template<class>
  struct pairwise_impl;

  template<class x, class... xs>
  struct pairwise_impl<list<x, xs...>>
  {
    template<class C, class F, class y, class... ys>
    using f = typename JLN_MP_TRACE_F(C)::template f<
      typename F::template f<xs, ys>...
    >;
  };

  template<class x>
  struct pairwise_impl<list<x>>
  {
    template<class C, class F, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct pairwise_impl<list<>>
  {
    template<class C, class F>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
