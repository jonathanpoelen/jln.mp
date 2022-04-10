#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    constexpr int_ sliding_stride(int_ size, int_ stride);

    template<int_ size, int_ stride, int_>
    struct mk_sliding;
  }
  /// \endcond

  /// \ingroup list

  /// Returns sliding windows of width \c size.
  /// \pre `stride != 0`
  /// \pre `size >= 0`
  /// \treturn \sequence of \list
  /// Given a sequence and a count n, place a window over the first n elements of the underlying range. Return the contents of that window as the first element of the adapted range, then slide the window forward one element at a time until hitting the end of the underlying range.
  /// \semantics
  ///     If `stride < 0`, then `stride = stride + size`
  ///     If `sizeof...(xs) < size`, then `f = C::f<xs...>`
  ///     If `stride > 1`, the last window may be smaller than \c size
  template<class size, class stride, class C = listify>
  using sliding_with_stride = typename detail::mk_sliding<
    size::value, stride::value,
    detail::sliding_stride(size::value, stride::value)
  >::template f<C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using sliding_with_stride_c = typename detail::mk_sliding<size, stride,
    detail::sliding_stride(size, stride)
  >::template f<C>;

  template<class size, class C = listify>
  using sliding = sliding_with_stride_c<size::value, 1, C>;

  template<int_ size, class C = listify>
  using sliding_c = sliding_with_stride_c<size, 1, C>;

  namespace emp
  {
    template<class L, class size, class stride, class C = mp::listify>
    using sliding_with_stride = unpack<L, mp::sliding_with_stride<size, stride, C>>;

    template<class L, int_ size, int_ stride, class C = mp::listify>
    using sliding_with_stride_c = unpack<L, mp::sliding_with_stride_c<size, stride, C>>;

    template<class L, class size, class C = mp::listify>
    using sliding = unpack<L, mp::sliding<size, C>>;

    template<class L, int_ size, class C = mp::listify>
    using sliding_c = unpack<L, mp::sliding_c<size, C>>;
  }
}


#include <jln/mp/algorithm/zip.hpp>
#include <jln/mp/algorithm/pairwise.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/group_n.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/slice.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int_ sliding_stride(int_ size, int_ stride)
  {
    if (!stride || size < 1) {
      return size == 0 ? -2 : -1;
    }

    if (stride < 0) {
      stride += size;
      if (stride <= 0) {
        return -1;
      }
    }

    return stride;
  }

  template<int>
  struct _sliding;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::_sliding<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, size, stride, xs...>;
  };

  template<int_ size, int_, int_ stride>
  struct mk_sliding
  {
    template<class C>
    using f = sliding_<size, stride, optimize_useless_transform_unpack_t<C>>;
  };

  template<class C>
  struct sliding_nostride
  {};

  template<class C>
  struct sliding_0size
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -1>
  {
    template<class C>
    using f = sliding_nostride<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -2>
  {
    template<class C>
    using f = sliding_0size<C>;
  };

  constexpr int_ slinding_pivot(int_ nx, int_ size, int_ stride)
  {
    return nx - (nx - size + stride - 1) / stride * stride - 1;
  }

  constexpr int sliding_select(int n, int_ size, int_ stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : size == 1 ? (stride == 1 ? 2 : 3)  // C<list<xs>...> / slice<0, n/stride, stride>
      : stride > n ? 9                     // take_front
      : stride == 1 ? (size == 2 ? 4 : 5)  // common case
      : stride == size ? 6                 // group_n
      // slice<zip_longest> / slice<zip>
      : ((n - size) % stride) ? (slinding_pivot(n, size, stride) < 0 ? 7 : 8) : 7;
  }

  template<>
  struct _sliding<-1>
  {};

  // sizeof...(xs) == 0
  template<>
  struct _sliding<0>
  {
    template<class C, int_, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  // sizeof...(xs) < size
  template<>
  struct _sliding<1>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs...>);
  };

  // size=1  stride=1
  template<>
  struct _sliding<2>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs>...);
  };

  // size=1  stride!=1
  template<>
  struct _sliding<3>
  {
    template<class C, int_, int_ stride, class... xs>
    using f = typename _slice<1>
      ::template f<0, (sizeof...(xs) + stride - 1) / stride, stride, transform<listify, C>, sizeof...(xs)>
      ::template f<xs...>;
  };

  // stride>size
  template<>
  struct _sliding<9>
  {
    template<class C, int_ size, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename rotate_c<size, drop_front_c<sizeof...(xs)-size>>::template f<xs...>
    );
  };

  // size=2  stride=1  (pairwise)
  template<>
  struct _sliding<4>
  {
    template<class C, int_, int_, class... xs>
    using f = typename detail::pairwise_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, listify, xs...>
      ;
  };

  // size>2  stride=1
  template<>
  struct _sliding<5>
  {
    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, class drop_front>
        using g = _tee<zip<C>, rotate_c<i-size, drop_front>...>;
      };
    };

    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<C, size-1, drop_front_c<size-1>>
      ::template f<xs...>;
  };

  // stride=size (group_n)
  template<>
  struct _sliding<6>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), lift_c<_group_n_impl>
    >::template f<C, size, xs...>;
  };

  // size>1  stride>1  (all list = size)
  template<>
  struct _sliding<7>
  {
    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, int_ stride>
        using g = _tee<zip<C>, slice_c<i, size, stride>...>;
      };
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<C, (sizeof...(xs) - size) / stride + 1, stride>
      ::template f<xs...>;
  };

  constexpr int_ slinding8_pivot(int_ nx, int_ size, int_ stride)
  {
    int_ r = slinding_pivot(nx, size, stride);
    return r < 0 ? size : r;
  }

  // size>1  stride>1  (last list < size)
  template<>
  struct _sliding<8>
  {
    template<class F, class C>
    struct adjust
    {
      template<class x, class... xs>
      using f = typename C::template f<xs..., typename F::template f<x>>;
    };

    struct impl
    {
      template<int_... i>
      struct f
      {
        template<class C, int_ size, int_ stride, int_ pivot>
        using g = _tee<zip<
          rotate_c<-1, adjust<unpack<rotate_c<-1, pop_front<>>>, C>>
        >, slice_c<i, size - (pivot < i), stride,
          typename conditional_c<(pivot < i)>::template f<push_back<void>, listify>
        >...>;
      };
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename emp::make_int_sequence_v_c<size, impl>
      ::template g<
        C,
        (sizeof...(xs) - size) / stride + 2,
        stride,
        slinding8_pivot(sizeof...(xs), size, stride)
      >
      ::template f<xs...>;
  };
}
/// \endcond
