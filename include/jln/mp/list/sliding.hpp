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
    constexpr int_t sliding_stride(int_t size, int_t stride);

    template<int_t size, int_t stride>
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
  ///   If `stride == 0 || size <= 0`, then the result sequence is empty
  ///   \code
  ///   strided_sliding_with_c<3, 1, F, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<F::f<_0, _1, _2>, F::f<_1, _2, _3>, F::f<_2, _3, _4>>
  ///
  ///   strided_sliding_with_c<3, 2, F, C>::f<_0, _1, _2, _3, _4>
  ///   ==
  ///   C::f<F::f<_0, _1, _2>, F::f<_2, _3, _4>>
  ///   \endcode
  template<int_t size, int_t stride = 1, class F = listify, class C = listify>
  using strided_sliding_with_c = typename detail::mk_sliding<size,
    detail::sliding_stride(size, stride)
  >::template f<C, F>;

  template<class size, class stride = number<1>, class F = listify, class C = listify>
  using strided_sliding_with = strided_sliding_with_c<size::value, stride::value, F, C>;

  template<class size, class stride = number<1>, class C = listify>
  using strided_sliding = strided_sliding_with_c<size::value, stride::value, listify, C>;

  template<int_t size, int_t stride = 1, class C = listify>
  using strided_sliding_c = strided_sliding_with_c<size, stride, listify, C>;

  template<class size, class F = listify, class C = listify>
  using sliding_with = strided_sliding_with_c<size::value, 1, F, C>;

  template<int_t size, class F = listify, class C = listify>
  using sliding_with_c = strided_sliding_with_c<size, 1, F, C>;

  template<class size, class C = listify>
  using sliding = strided_sliding_with_c<size::value, 1, listify, C>;

  template<int_t size, class C = listify>
  using sliding_c = strided_sliding_with_c<size, 1, listify, C>;


  namespace emp
  {
    template<class L, class size, class stride = number<1>, class F = listify, class C = mp::listify>
    using strided_sliding_with = typename detail::_unpack<
      mp::strided_sliding_with_c<size::value, stride::value, F, C>, L>::type;

    template<class L, int_t size, int_t stride = 1, class F = listify, class C = mp::listify>
    using strided_sliding_with_c = typename detail::_unpack<
      mp::strided_sliding_with_c<size, stride, F, C>, L>::type;

    template<class L, class size, class stride = number<1>, class C = mp::listify>
    using strided_sliding = typename detail::_unpack<
      mp::strided_sliding_with_c<size::value, stride::value, listify, C>, L>::type;

    template<class L, int_t size, int_t stride = 1, class C = mp::listify>
    using strided_sliding_c = typename detail::_unpack<
      mp::strided_sliding_with_c<size, stride, listify, C>, L>::type;

    template<class L, class size, class F = listify, class C = mp::listify>
    using sliding_with = typename detail::_unpack<
      mp::strided_sliding_with_c<size::value, 1, F, C>, L>::type;

    template<class L, int_t size, class F = listify, class C = mp::listify>
    using sliding_with_c = typename detail::_unpack<
      mp::strided_sliding_with_c<size, 1, F, C>, L>::type;

    template<class L, class size, class C = mp::listify>
    using sliding = typename detail::_unpack<
      mp::strided_sliding_with_c<size::value, 1, listify, C>, L>::type;

    template<class L, int_t size, class C = mp::listify>
    using sliding_c = typename detail::_unpack<
      mp::strided_sliding_with_c<size, 1, listify, C>, L>::type;
  }
}


#include <jln/mp/algorithm/zip.hpp>
#include <jln/mp/algorithm/pairwise.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/lookup.hpp>
#include <jln/mp/list/slice.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int_t sliding_stride(int_t size, int_t stride)
  {
    if (!stride || size < 1) {
      return -1;
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

  constexpr int sliding_select(int n, int_t size, int_t stride);

  template<int_t size, int_t stride, class F, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::sliding_impl<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, F, size, stride, xs...>;
  };

  // size == 1 ; stride != 1
  template<int_t stride, class F, class C>
  struct sliding_<1, stride, F, C>
  {
    template<class... xs>
    using f = typename detail::sliding_impl<sizeof...(xs) ? 3 : 0>
      ::template f<C, F, 1, stride, xs...>;
  };

  template<int_t size, int_t stride>
  struct mk_sliding
  {
    template<class C, class F>
    using f = sliding_<size, stride, F, C>;
  };

  template<class C>
  struct sliding_0
    : call_trace_xs_0<C>
  {};

  template<int_t size>
  struct mk_sliding<size, -1>
  {
    template<class C, class F>
    using f = sliding_0<C>;
  };

  template<>
  struct mk_sliding<1, 1>
  {
    template<class C, class F>
    using f = transform<F, C>;
  };

  constexpr int sliding_select(int n, int_t size, int_t stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : stride > n ? 9                     // take_front_max
      : stride == 1 ? (size == 2 ? 4 : size < 9 ? 5 : 51)  // common case
      : stride == size ? (n % size ? 61 : 6)  // batched
      // slice<zip_longest> / slice<zip>
      : (stride >= size ? (n - 1) % stride >= size - 1 : (n - size) % stride == 0) ? 7 : 8;
  }


  // sizeof...(xs) == 0
  template<>
  struct sliding_impl<0>
  {
    template<class C, class F, int_t, int_t, class...>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };


  // sizeof...(xs) <= size
  template<>
  struct sliding_impl<1>
  {
    template<class C, class F, int_t, int_t, class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename JLN_MP_TRACE_F(F)::template f<xs...>);
  };


  // size == 1 ; stride != 1
  template<>
  struct sliding_impl<3>
  {
    template<class C, class F, int_t, int_t stride, class... xs>
    using f = typename strided_slice_impl<0, (sizeof...(xs) - 1) % stride>
      ::template impl<transform<F, C>, stride, sizeof...(xs)>
      ::template f<xs...>;
  };


  // stride > size  (take_front_max)
  template<>
  struct sliding_impl<9>
  {
    template<class C, class F, int_t size, int_t stride, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<sizeof...(xs) <= size>
      ::template f<JLN_MP_TRACE_F(F), take_front_c<static_cast<unsigned>(size), F>>
      ::template f<xs...>
    );
  };


  // size == 2 ; stride == 1  (pairwise)
  template<>
  struct sliding_impl<4>
  {
    template<class C, class F, int_t, int_t, class... xs>
    using f = typename pairwise_with<F, C>::template f<xs...>;
  };


  // 2 < size < 9 ; stride == 1
  template<class, int_t... i>
  struct sliding5_impl
  {
    template<class C, class F, int_t size, class drop_front>
    using impl = _tee<zip_with<F, C>,
      rotate_c<i-size, drop_front>...,
      drop_front
    >;
  };


  // size > 2 ; stride == 1
  template<>
  struct sliding_impl<5>
  {
    template<class C, class F, int_t size, int_t, class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(size-1, sliding5_impl)
      ::template impl<C, F, size-1, drop_front_c<size-1>>
      ::template f<xs...>;
  };


  template<class, int... ns>
  struct sliding_inner
  {
    template<class C, class Indexed, int i>
    using f = typename C::template f<typename JLN_MP_D_INDEXED_GET(ns+i, Indexed)...>;
  };

  template<class, int... outer_index>
  struct sliding_outer
  {
      template<class F, class C, class InnerC, class Indexed>
      using f = typename C::template f<typename F::template f<InnerC, Indexed, outer_index>...>;
  };

  template<int_t n>
  using make_sliding_inner = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, sliding_inner);

  template<int_t n>
  using make_sliding_outer = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, sliding_outer);

  // size > 8 ; stride == 1
  template<>
  struct sliding_impl<51>
  {
    template<class C, class F, int_t size, int_t /*stride*/, class... xs>
    using f = typename make_sliding_outer<sizeof...(xs) - size + 1>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  template<class, int... outer_index>
  struct strided_sliding_outer
  {
    template<int d>
    struct strided
      : sliding_outer<int, outer_index * d...>
    {};
  };

  template<int_t n, int_t stride>
  using make_strided_sliding_outer
    = typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, n, strided_sliding_outer)
      ::template strided<stride>;


  // stride == size  (batched) (all list == size)
  template<>
  struct sliding_impl<6>
  {
    template<class C, class F, int_t size, int_t /*stride*/, class... xs>
    using f = typename make_strided_sliding_outer<sizeof...(xs) / size, size>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  // stride == size  (batched) (last list < size)
  template<>
  struct sliding_impl<61>
  {
    template<class C, class F, int_t size, int_t n, class Indexed>
    using impl = typename join<C>::template f<
      typename make_strided_sliding_outer<n / size, size>
        ::template f<make_sliding_inner<size>, listify, F, Indexed>,
      list<typename make_sliding_inner<n % size>
        ::template f<F, Indexed, n / size * size>>
    >;

    template<class C, class F, int_t size, int_t /*stride*/, class... xs>
    using f = impl<
      JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
      size, sizeof...(xs), build_indexed_v<xs...>
    >;
  };


  // size > 1 ; stride > 1  (all list = size)
  template<>
  struct sliding_impl<7>
  {
    template<class C, class F, int_t size, int_t stride, class... xs>
    using f = typename make_strided_sliding_outer<(sizeof...(xs) - size) / stride + 1, stride>
      ::template f<
        make_sliding_inner<size>,
        JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
        build_indexed_v<xs...>
      >;
  };


  // size > 1 ; stride > 1  (last list < size)
  template<>
  struct sliding_impl<8>
  {
    template<class C, class F, int_t size, int_t stride, int_t ns, class Indexed,
      int_t n = (ns - size) / stride + 1>
    using impl = typename join<C>::template f<
      typename make_strided_sliding_outer<n, stride>
        ::template f<make_sliding_inner<size>, listify, F, Indexed>,
      list<typename make_sliding_inner<ns - n * stride>
        ::template f<F, Indexed, n * stride>>
    >;

    template<class C, class F, int_t size, int_t stride, class... xs>
    using f = impl<
      JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F),
      size, stride, sizeof...(xs), build_indexed_v<xs...>
    >;
  };
}
/// \endcond
