#pragma once

#include "../list/list.hpp"
#include "../number/operators.hpp"
#include "../config/enumerate.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int n, class Cmp>
    struct _sort;
  }

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
    using sort = eager<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = eager<L, mp::sort<Cmp, C>>;
  }
}

#include "prepend.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"

namespace jln::mp
{
  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::_sort<detail::min(3, sizeof...(xs)), Cmp>
      ::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<class x, class y, class z = list<>, class = true_>
  struct _merge;

  template<class, class, class, class, class = true_>
  struct _merge_impl
  {};

  constexpr int _fast_merge_impl_select(bool b, int xn, int yn)
  {
    return b ? (yn >= 4) : (xn >= 4) + 2;
  }

  template<int>
  struct _fast_merge_impl;

  template<>
  struct _fast_merge_impl<0>
  {
    template<class, class, class, class>
    struct f
    {};

    template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
    struct f<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
    : _merge_impl<list<xh, xt...>, list<yt...>, list<zs..., yh>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<1>
  {
    template<class, class, class, class, class = true_>
    struct f
    {};

    template<
      class xh, class... xt,
      class yh0, class yh1, class yh2, class yh3, class yh4, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh, xt...>,
      list<yh0, yh1, yh2, yh3, yh4, yt...>,
      list<zs...>, cmp,
      number<bool(call<cmp, yh4, xh>::value)>>
    : _merge_impl<list<xh, xt...>, list<yt...>, list<zs..., yh0, yh1, yh2, yh3, yh4>, cmp>
    {};

    template<
      class xh, class... xt,
      class yh0, class yh1, class yh2, class yh3, class yh4, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh, xt...>,
      list<yh0, yh1, yh2, yh3, yh4, yt...>,
      list<zs...>, cmp,
      number<!bool(call<cmp, yh4, xh>::value)>>
    : _merge_impl<list<xh, xt...>, list<yh1, yh2, yh3, yh4, yt...>, list<zs..., yh0>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<2>
  {
    template<class, class, class, class>
    struct f
    {};

    template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
    struct f<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
    : _merge_impl<list<xt...>, list<yh, yt...>, list<zs..., xh>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<3>
  {
    template<class, class, class, class, class = true_>
    struct f
    {};

    template<
      class xh0, class xh1, class xh2, class xh3, class xh4, class... xt,
      class yh, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh0, xh1, xh2, xh3, xh4, xt...>,
      list<yh, yt...>,
      list<zs...>, cmp,
      number<!bool(call<cmp, yh, xh4>::value)>>
    : _merge_impl<list<xt...>, list<yh, yt...>, list<zs..., xh0, xh1, xh2, xh3, xh4>, cmp>
    {};

    template<
      class xh0, class xh1, class xh2, class xh3, class xh4, class... xt,
      class yh, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh0, xh1, xh2, xh3, xh4, xt...>,
      list<yh, yt...>,
      list<zs...>, cmp,
      number<bool(call<cmp, yh, xh4>::value)>>
    : _merge_impl<list<xh1, xh2, xh3, xh4, xt...>, list<yh, yt...>, list<zs..., xh0>, cmp>
    {};
  };

  template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
  struct _merge_impl<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
  : _fast_merge_impl<_fast_merge_impl_select(
    bool(call<cmp, yh, xh>::value), sizeof...(xt), sizeof...(yt)
  )>::template f<
    list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
  {};

  template<class... xs, class... zs, class cmp>
  struct _merge_impl<list<xs...>, list<>, list<zs...>, cmp>
  {
    template<class x, class y>
    using part = typename _merge<emp::prepend<x, xs...>, y, list<zs...>>::template f<cmp>;

    using type = list<zs..., xs...>;
  };

  template<class... ys, class... zs, class cmp>
  struct _merge_impl<list<>, list<ys...>, list<zs...>, cmp>
  {
    template<class x, class y>
    using part = typename _merge<x, emp::prepend<y, ys...>, list<zs...>>::template f<cmp>;

    using type = list<zs..., ys...>;
  };

  template<class... xs, class... ys, class z>
  struct _merge<list<xs...>, list<ys...>, z, number<
    // x.size + y.size >= 100, unless empty list
    (unsigned{sizeof...(xs)-1LL} + unsigned{sizeof...(ys)-1LL} >= 98u)>>
  {
    using xm = number<(sizeof...(xs) + 1) / 2>;
    using ym = number<(sizeof...(ys) + 1) / 2>;

    using xl = call<take<xm>, xs...>;
    using yl = call<take<ym>, ys...>;

    using xr = call<drop<xm>, xs...>;
    using yr = call<drop<ym>, ys...>;

    using l = _merge<xl, yl, z>;

    template<class cmp>
    using f = typename l::template f<cmp>::template part<xr, yr>;
  };

  template<class x, class y, class z, class>
  struct _merge
  {
    template<class cmp>
    using f = _merge_impl<x, y, z, cmp>;
  };

  template<class x, class z>
  struct _merge<x, list<>, z>
  {
    template<class cmp>
    using f = _merge_impl<x, list<>, z, cmp>;
  };

  template<class y, class z>
  struct _merge<list<>, y, z>
  {
    template<class cmp>
    using f = _merge_impl<list<>, y, z, cmp>;
  };

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
