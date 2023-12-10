// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
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
  /// Given a sequence and a count n, place a window over the first n elements of the underlying range.
  /// Return the contents of that window as the first element of the adapted range,
  /// then slide the window forward one element at a time until hitting the end of the underlying range.
  /// \semantics
  ///   If `stride < 0`, then `stride = stride + size`
  ///   If `sizeof...(xs) < size`, then `f = C::f<xs...>`
  ///   If `stride > 1`, the last window may be smaller than \c size
  ///   \code
  ///   sliding_with_stride_c<3, 1, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<list<_0, _1, _2>, list<_1, _2, _3>, list<_2, _3, _4>>
  ///
  ///   sliding_with_stride_c<3, 2, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<list<_0, _1, _2>, list<_2, _3, _4>>
  ///   \endcode
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
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/batched.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/pop_front.hpp>
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
  struct sliding_impl;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::sliding_impl<detail::sliding_select(
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
      : stride == size ? 6                 // batched
      // slice<zip_longest> / slice<zip>
      : ((n - size) % stride) ? (slinding_pivot(n, size, stride) < 0 ? 7 : 8) : 7;
  }

  template<>
  struct sliding_impl<-1>
  {};

  // sizeof...(xs) == 0
  template<>
  struct sliding_impl<0>
  {
    template<class C, int_, int_, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  // sizeof...(xs) < size
  template<>
  struct sliding_impl<1>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs...>);
  };

  // size=1  stride=1
  template<>
  struct sliding_impl<2>
  {
    template<class C, int_, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C, list<xs>...);
  };

  // size=1  stride!=1
  template<>
  struct sliding_impl<3>
  {
    template<class C, int_, int_ stride, class... xs>
    using f = typename strided_slice_impl<0, sizeof...(xs) ? (sizeof...(xs) - 1) % stride : 0>
      ::template impl<transform<listify, C>, stride, sizeof...(xs)>
      ::template f<xs...>;
  };

  // stride>size
  template<>
  struct sliding_impl<9>
  {
    template<class C, int_ size, int_, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename rotate_impl<size>::template f<size, drop_front_c<sizeof...(xs)-size>, xs...>
    );
  };

  // size=2  stride=1  (pairwise)
  template<>
  struct sliding_impl<4>
  {
    template<class C, int_, int_, class... xs>
    using f = typename pairwise<C>::template f<xs...>;
  };

  template<class, int_... i>
  struct sliding5_impl
  {
    template<class C, int_ size, class drop_front>
    using f = _tee<zip<C>, rotate_c<int_(i)-size, drop_front>...>;
  };

  // size>2  stride=1
  template<>
  struct sliding_impl<5>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(size, sliding5_impl)
      ::template f<C, size-1, drop_front_c<size-1>>
      ::template f<xs...>;
  };

  // stride=size (batched)
  template<>
  struct sliding_impl<6>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename batched_with_c<size, listify, C>::template f<xs...>;
  };

  template<class, int_... i>
  struct sliding7_impl
  {
    template<class C, int_ size, int_ stride>
    using f = _tee<zip<C>, slice_with_step_c<i, size, stride>...>;
  };

  // size>1  stride>1  (all list = size)
  template<>
  struct sliding_impl<7>
  {
    template<class C, int_ size, int_ stride, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(size, sliding7_impl)
      ::template f<C, (sizeof...(xs) - size) / stride + 1, stride>
      ::template f<xs...>;
  };

  constexpr int_ slinding8_pivot(int_ nx, int_ size, int_ stride)
  {
    int_ r = slinding_pivot(nx, size, stride);
    return r < 0 ? size : r;
  }

  template<class C>
  struct adjust
  {
    template<class x, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C,
      xs...,
      typename _unpack<rotate_c<-1, pop_front<>>, x>::type
    );
  };

  template<>
  struct adjust<listify>
  {
    template<class x, class... xs>
    using f = list<
      xs...,
      typename _unpack<rotate_c<-1, pop_front<>>, x>::type
    >;
  };

  template<class, int_... i>
  struct sliding8_impl
  {
    template<class C, int_ size, int_ stride, int_ pivot>
    using f = _tee<
      zip<rotate_c<-1, adjust<C>>>,
      slice_with_step_c<i, size - (pivot < i), stride,
        typename conditional_c<(pivot < i)>::template f<push_back<void>, listify>
      >...
    >;
  };

  // size>1  stride>1  (last list < size)
  template<>
  struct sliding_impl<8>
  {
    template<class C, int_ size, int_ stride, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(size, sliding8_impl)
      ::template f<
        C,
        (sizeof...(xs) - size) / stride + 2,
        stride,
        slinding8_pivot(sizeof...(xs), size, stride)
      >
      ::template f<xs...>;
  };
}
/// \endcond
