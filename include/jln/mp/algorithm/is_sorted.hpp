#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned>
    struct _is_sorted;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks wheteher a \sequence is sorted.
  /// \treturn \number
  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE((C),
      typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
      ::template f<Cmp, xs...>
    );
  };

  /// \cond
  template<class Cmp>
  struct is_sorted<Cmp, identity>
  {
    template<class... xs>
    using f = typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
      ::template f<Cmp, xs...>;
  };
  /// \endcond

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}


#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/list/push_front.hpp>
#include <jln/mp/algorithm/zip.hpp>
#include <jln/mp/algorithm/rotate.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _is_sorted<0>
  {
    template<class Cmp>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<1>
  {
    template<class Cmp, class x>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<2>
  {
    template<class Cmp, class x, class y>
    using f = number<!JLN_MP_TRACE_F(Cmp)::template f<y, x>::value>;
  };

  template<>
  struct _is_sorted<3>
  {
    template<class Cmp, class x, class y, class... xs>
    using f = typename zip_with<Cmp, or_<not_<>>>::template f<
      list<y, xs...>,
      rotate_c<-1, pop_front<>>::f<x, y, xs...>
    >;
  };
}
/// \endcond
