#pragma once

#include "../list/list.hpp"
#include "../list/join.hpp"
#include "../functional/call.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  namespace detail
  {
    constexpr int sort_select(int n)
    {
      return n <= 1 ? 0 : n == 2 ? 1 : 2;
    }

    template<int n, class Cmp, class C>
    struct _sort;
  }

  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = typename detail::_sort<detail::sort_select(sizeof...(xs)), Cmp, C>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = eager<L, mp::sort<Cmp, C>>;

  }

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;
}

#include "../utility/conditional.hpp"
#include "find.hpp"
#include "swap_index.hpp"
#include "reverse.hpp"
#include "../list/push_back.hpp"
#include "../list/push_front.hpp"
#include "../list/pop_front.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../list/at.hpp"
#include "../functional/fork.hpp"
#include "../functional/flip.hpp"
#include "../number/operators.hpp"

namespace jln::mp::detail
{
  constexpr int sort_impl_select(int n)
  {
    return n <= 3 ? n : 0;
  }

  template<class seq1, class seq2>
  struct _sort_merge;

  template<class...>
  class rlist;

  template<bool>
  struct mk_rlist2_2
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = rlist<rlist<x0, x1>, y0, rlist<y1>>;
  };

  template<bool, bool>
  struct mk_rlist2_2_s2
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = rlist<rlist<x0, y0>, x1, rlist<y1>>;
  };

  template<>
  struct mk_rlist2_2_s2<true, false>
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = rlist<rlist<y0, x0>, x1, rlist<y1>>;
  };

  template<>
  struct mk_rlist2_2_s2<false, true>
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = rlist<rlist<x0, y0>, y1, rlist<x1>>;
  };

  template<bool>
  struct mk_rlist2_2_s3_m
  {
    template<class x0, class x1, class y0, class y1>
    using f = rlist<rlist<y0, x0>, y1, rlist<x1>>;
  };

  template<>
  struct mk_rlist2_2_s3_m<true>
  {
    template<class x0, class x1, class y0, class y1>
    using f = rlist<rlist<y0, y1>, x0, rlist<x1>>;
  };

  template<>
  struct mk_rlist2_2_s2<true, true>
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = typename mk_rlist2_2_s3_m<
      bool(call<Cmp, y1, x0>::value)
    >::template f<x0, x1, y0, y1>;
  };

  template<>
  struct mk_rlist2_2<true>
  {
    template<class Cmp, class x0, class x1, class y0, class y1>
    using f = typename mk_rlist2_2_s2<
      bool(call<Cmp, y0, x0>::value),
      bool(call<Cmp, y1, x1>::value)
    >::template f<Cmp, x0, x1, y0, y1>;
  };

  template<class x0, class x1, class y0, class y1>
  struct _sort_merge<rlist<x0, x1>, rlist<y0, y1>>
  {
    template<class Cmp>
    using f = typename mk_rlist2_2<bool(call<Cmp, y0, x1>::value)>
      ::template f<Cmp, x0, x1, y0, y1>;
  };


  template<bool>
  struct mk_rlist2_3
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<a, b>, c, rlist<d, e>>;
  };

  template<bool, bool>
  struct mk_rlist2_3_s2
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<a, c>, b, rlist<d, e>>;
  };

  template<>
  struct mk_rlist2_3_s2<true, false>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, a>, b, rlist<d, e>>;
  };

  template<bool>
  struct mk_rlist2_3_s3
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<a, c>, d, rlist<b, e>>;
  };

  template<>
  struct mk_rlist2_3_s3<true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<a, c>, d, rlist<e, b>>;
  };

  template<>
  struct mk_rlist2_3_s2<false, true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = typename mk_rlist2_3_s3<
      bool(call<Cmp, e, b>::value)
    >::template f<Cmp, a, b, c, d, e>;
  };

  template<bool, bool>
  struct mk_rlist2_3_s3_2
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, a>, d, rlist<b, e>>;
  };

  template<>
  struct mk_rlist2_3_s3_2<true, false>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, a>, d, rlist<e, b>>;
  };

  template<>
  struct mk_rlist2_3_s3_2<false, true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, d>, a, rlist<b, e>>;
  };

  template<bool>
  struct mk_rlist2_3_s3_2_s2
  {
    template<class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, d>, a, rlist<e, b>>;
  };

  template<>
  struct mk_rlist2_3_s3_2_s2<true>
  {
    template<class a, class b, class c, class d, class e>
    using f = rlist<rlist<c, d>, e, rlist<a, b>>;
  };

  template<>
  struct mk_rlist2_3_s3_2<true, true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = typename mk_rlist2_3_s3_2_s2<
      bool(call<Cmp, e, a>::value)
    >::template f<a, b, c, d, e>;
  };

  template<>
  struct mk_rlist2_3_s2<true, true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = typename mk_rlist2_3_s3_2<
      bool(call<Cmp, e, b>::value),
      bool(call<Cmp, d, a>::value)
    >::template f<Cmp, a, b, c, d, e>;
  };

  template<>
  struct mk_rlist2_3<true>
  {
    template<class Cmp, class a, class b, class c, class d, class e>
    using f = typename mk_rlist2_3_s2<
      bool(call<Cmp, c, a>::value),
      bool(call<Cmp, d, b>::value)
    >::template f<Cmp, a, b, c, d, e>;
  };

  template<class a, class b, class c, class d, class e>
  struct _sort_merge<rlist<a, b>, rlist<c, d, e>>
  {
    template<class Cmp>
    using f = typename mk_rlist2_3<bool(call<Cmp, c, b>::value)>
      ::template f<Cmp, a, b, c, d, e>;
  };

  template<int n, class Cmp>
  struct _sort_impl
  {
    template<class... xs>
    using f = typename _sort_merge<
      call<take_c<sizeof...(xs) / 2,
        _sort_impl<sort_impl_select(sizeof...(xs) / 2), Cmp>>, xs...>,
      call<drop_c<sizeof...(xs) / 2,
        _sort_impl<sort_impl_select(sizeof...(xs) - sizeof...(xs) / 2), Cmp>>, xs...>
    >::template f<Cmp>;
  };

  template<class Cmp>
  struct _sort_impl<1, Cmp>
  {
    template<class x>
    using f = rlist<x>;
  };

  template<bool>
  struct mk_rlist2
  {
    template<class... xs>
    using f = rlist<xs...>;
  };

  template<>
  struct mk_rlist2<true>
  {
    template<class x, class y>
    using f = rlist<y, x>;
  };

  template<class Cmp>
  struct _sort_impl<2, Cmp>
  {
    template<class x, class y>
    using f = typename mk_rlist2<bool(call<Cmp, y, x>::value)>
      ::template f<x, y>;
  };

  template<bool, bool>
  struct mk_rlist3
  {
    template<class Cmp, class... xs>
    using f = rlist<xs...>;
  };

  template<>
  struct mk_rlist3<true, true>
  {
    template<class Cmp, class x, class y, class z>
    using f = rlist<z, y, x>;
  };

  template<bool>
  struct mk_rlist3_r
  {
    template<class x, class y, class z>
    using f = rlist<x, z, y>;
  };

  template<>
  struct mk_rlist3_r<true>
  {
    template<class x, class y, class z>
    using f = rlist<z, x, y>;
  };

  template<>
  struct mk_rlist3<false, true>
  {
    template<class Cmp, class x, class y, class z>
    using f = typename mk_rlist3_r<bool(call<Cmp, z, x>::value)>
      ::template f<x, y, z>;
  };

  template<bool>
  struct mk_rlist3_l
  {
    template<class x, class y, class z>
    using f = rlist<y, x, z>;
  };

  template<>
  struct mk_rlist3_l<true>
  {
    template<class x, class y, class z>
    using f = rlist<y, z, x>;
  };

  template<>
  struct mk_rlist3<true, false>
  {
    template<class Cmp, class x, class y, class z>
    using f = typename mk_rlist3_l<bool(call<Cmp, z, x>::value)>
      ::template f<x, y, z>;
  };

  template<class Cmp>
  struct _sort_impl<3, Cmp>
  {
    template<class x, class y, class z>
    using f = typename mk_rlist3<bool(call<Cmp, y, x>::value), bool(call<Cmp, z, y>::value)>
      ::template f<Cmp, x, y, z>;
  };

  template<int n, class Cmp, class C>
  struct _sort
  {
    template<class... xs>
    using f = typename _sort_impl<sort_impl_select(sizeof...(xs)), Cmp>
      ::template f<xs...>;
  };

  template<class Cmp, class C>
  struct _sort<0, Cmp, C>
  {
    template<class... xs>
    using f = call<C, xs...>;
  };

  template<class Cmp, class C>
  struct _sort<1, Cmp, C>
  {
    template<class x, class y>
    using f = typename conditional_c<bool(call<Cmp, x, y>::value)>
      ::template f<flip<C>, C>
      ::template f<y, x>;
  };

}
