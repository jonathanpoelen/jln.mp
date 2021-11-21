#pragma once

#include <jln/mp/number/operators.hpp>

#include <type_traits>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool, bool>
    struct _dispatch_merge;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Merges two \list into one sorted \sequence.
  /// \pre `emp::is_sorted<seq1, Cmp>`
  /// \pre `emp::is_sorted<seq2, Cmp>`
  /// \post \c emp::is_sorted<result...>
  /// \treturn \sequence
  template<class Cmp = less<>, class C = listify>
  struct merge
  {
    template<class seq1, class seq2>
    using f = typename unpack<C>::template f<
      typename detail::_dispatch_merge<
        std::is_same<seq1, list<>>::value,
        std::is_same<seq2, list<>>::value
      >
      ::template f<seq1, seq2>
      ::template f<JLN_MP_TRACE_F(Cmp)>::type
    >;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using merge = unpack<L, mp::merge<Cmp, C>>;
  }
}


#include <jln/mp/list/prepend.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/detail/type_identity.hpp>

namespace jln::mp
{
  /// \cond
  template<class Cmp>
  struct merge<Cmp, listify>
  {
    template<class seq1, class seq2>
    using f = typename detail::_dispatch_merge<
      std::is_same<seq1, list<>>::value,
      std::is_same<seq2, list<>>::value
    >::template f<seq1, seq2>
    ::template f<JLN_MP_TRACE_F(Cmp)>::type;
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class, class, class, class>
  struct _merge_impl
  {};

  template<class x, class y, class z = list<>, class = true_>
  struct _merge;

  template<bool, bool>
  struct _dispatch_merge
  {
    template<class x, class y>
    using f = _merge<x, y>;
  };

  template<>
  struct _dispatch_merge<true, true>
  {
    template<class x, class y>
    using f = always<type_identity<list<>>>;
  };

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
      number<bool(cmp::template f<yh4, xh>::value)>>
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
      number<!bool(cmp::template f<yh4, xh>::value)>>
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
      number<!bool(cmp::template f<yh, xh4>::value)>>
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
      number<bool(cmp::template f<yh, xh4>::value)>>
    : _merge_impl<list<xh1, xh2, xh3, xh4, xt...>, list<yh, yt...>, list<zs..., xh0>, cmp>
    {};
  };

  template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
  struct _merge_impl<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
  : _fast_merge_impl<_fast_merge_impl_select(
    bool(cmp::template f<yh, xh>::value), sizeof...(xt), sizeof...(yt)
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
    (sizeof...(xs) && sizeof...(ys) && sizeof...(xs) > 0 && sizeof...(ys) >= 100u)>>
  {
    using xm = number<(sizeof...(xs) + 1) / 2>;
    using ym = number<(sizeof...(ys) + 1) / 2>;

    using xr = typename drop_front<xm>::template f<xs...>;
    using yr = typename drop_front<ym>::template f<ys...>;

    using l = _merge<
      typename take_front<xm>::template f<xs...>,
      typename take_front<ym>::template f<ys...>,
      z
    >;

    template<class cmp>
    using f = typename l::template f<cmp>::template part<xr, yr>;
  };

  template<class x, class y, class z, class>
  struct _merge
  {
    template<class cmp>
    using f = _merge_impl<x, y, z, cmp>;
  };

  // could be deleted
  template<class x, class z>
  struct _merge<x, list<>, z>
  {
    template<class cmp>
    using f = _merge_impl<x, list<>, z, cmp>;
  };

  // could be deleted
  template<class y, class z>
  struct _merge<list<>, y, z>
  {
    template<class cmp>
    using f = _merge_impl<list<>, y, z, cmp>;
  };
}
/// \endcond
