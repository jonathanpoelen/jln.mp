#pragma once

#include "../list/listify.hpp"
#include "../number/operators.hpp"
#include "../detail/enumerate.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n, class Cmp>
    struct _sort;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Sorts the elements of a \sequence according to an ordering relation.
  /// \post \c is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = call<unpack<C>,
      typename detail::_sort<detail::min(3, sizeof...(xs)), Cmp>
      ::template f<xs...>>;
  };

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = unpack<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = unpack<L, mp::sort<Cmp, C>>;
  }
}


#include "merge.hpp"

namespace jln::mp
{
  /// \cond
  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::_sort<detail::min(3, sizeof...(xs)), Cmp>
      ::template f<xs...>;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct _sort<3, Cmp>
  {
    template<class... xs>
    using f = typename memoize_call<_merge<
      call<take_c<sizeof...(xs) / 2, _sort<min(3, sizeof...(xs) / 2), Cmp>>, xs...>,
      call<drop_c<sizeof...(xs) / 2, _sort<min(3, (sizeof...(xs) + 1) / 2), Cmp>>, xs...>
    >, Cmp>::type;
  };

  template<bool>
  struct mk_list2
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct mk_list2<true>
  {
    template<class x, class y>
    using f = list<y, x>;
  };

  template<class Cmp>
  struct _sort<2, Cmp>
  {
    template<class x, class y>
    using f = typename mk_list2<bool(call<Cmp, y, x>::value)>
      ::template f<x, y>;
  };

  template<class Cmp>
  struct _sort<1, Cmp>
  {
    template<class x>
    using f = list<x>;
  };

  template<class Cmp>
  struct _sort<0, Cmp>
  {
    template<class...>
    using f = list<>;
  };
}
/// \endcond
