// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C, int_t i, int_t ri>
    struct slice_impl;

    template<int_t i, int_t ri>
    struct strided_slice_impl;

    template<class C, int_t i, int_t ri>
    struct positive_slice_impl;

    template<int_t i, int_t ri>
    struct positive_strided_slice_impl;

    template<bool>
    struct negative_slice_select;

    template<bool>
    struct negative_strided_slice_select;

    // pre: start < 0
    // pre: count > 0
    // pre: step > 0
    // pre: n >= 0
    template<int_t start, int_t count, int_t step, int_t n,
      int_t i = n + start,
      int_t e = i + (count - 1) * step + 1,
      int_t ii
        = e <= 0
        ? -1
        : i < 0
        ? -i % step
        : i,
      int_t ri
        = e <= 0 || n <= ii
        ? -1
        : n - (n < e ? (n - 1 - ii) / step * step + ii + 1 : e)
    >
    using negative_strided_slice_dispatch = strided_slice_impl<
      ri == -1 ? -1 : ii,
      ri
    >;

    // pre: i >= 0
    // pre: count > 0
    // pre: step > 0
    template<int_t i, int_t count, int_t step,
      int_t e = i + (count - 1) * step + 1
    >
    using positive_strided_slice_dispatch = positive_strided_slice_impl<
      e <= 0 ? -1 : i < 0 ? -i % step : i,
      e <= 0 ? -1 : e
    >;

    // pre: start < 0
    // pre: count > 0
    // pre: n >= 0
    template<class C, int_t start, int_t count, int_t n,
      int_t e = n + start + count,
      int_t i
        = e <= 0
        ? -1
        : n < -start
        ? 0
        : n + start,
      int_t ri
        = e <= 0 || n <= i
        ? -1
        : n < e
        ? 0
        : n - e
    >
    using negative_slice_dispatch = slice_impl<
      C,
      ri == -1 ? -1 : i,
      ri
    >;

    // pre: i >= 0
    // pre: count > 0
    // pre: n >= 0
    template<class C, int_t i, int_t count, int_t e = i + count>
    using positive_slice_dispatch = positive_slice_impl<
      C,
      e <= 0 ? -1 : i < 0 ? 0 : i,
      e <= 0 ? -1 : e
    >;
  } // namespace jln::mp::detail
  /// \endcond


  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// A negative start represents an index starting from the end.
  /// \pre `0 < step || count == 0`
  /// \treturn \sequence
  template<int_t start, unsigned count, unsigned step = 1, class C = listify>
  struct strided_slice_c
    : detail::negative_strided_slice_select<start < 0>
    ::template impl<start, count, step, C>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class start, class count, class step = number<1>, class C = listify>
  using strided_slice = strided_slice_c<start::value, count::value, step::value, C>;

  template<int_t start, unsigned count, class C = listify>
  using slice_c = strided_slice_c<start, count, 1, C>;

  template<class start, class count, class C = listify>
  using slice = strided_slice_c<start::value, count::value, 1, C>;

  namespace emp
  {
    template<class L, class start, class count, class step = number<1>, class C = mp::listify>
    using strided_slice = typename detail::_unpack<
      strided_slice<start, count, step, C>, L>::type;

    template<class L, int_t start, unsigned count, unsigned step = 1, class C = mp::listify>
    using strided_slice_c = typename detail::_unpack<
      mp::strided_slice_c<start, count, step, C>, L>::type;

    template<class L, class start, class count, class C = mp::listify>
    using slice = typename detail::_unpack<
      mp::strided_slice_c<start::value, count::value, 1, C>, L>::type;

    template<class L, int_t start, unsigned count, class C = mp::listify>
    using slice_c = typename detail::_unpack<
      mp::strided_slice_c<start, count, 1, C>, L>::type;
  }
}


#include <jln/mp/algorithm/arrange.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/algorithm/compress.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp
{
  template<int_t start, unsigned count, class C>
  struct strided_slice_c<start, count, 1, C>
    : detail::negative_slice_select<start < 0>
    ::template impl<start, count, C>
  {};

  template<int_t start, unsigned step, class C>
  struct strided_slice_c<start, 0, step, C> : clear<C>
  {};

  // invalid
  template<int_t start, unsigned count, class C>
  struct strided_slice_c<start, count, 0, C>
  {};

  template<int_t start, class C>
  struct strided_slice_c<start, 0, 0, C> : clear<C>
  {};

  template<int_t start, class C>
  struct strided_slice_c<start, 0, 1, C> : clear<C>
  {};
}// namespace jln::mp

namespace jln::mp::detail
{
  template<>
  struct negative_slice_select<true>
  {
    template<int_t start, unsigned count, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_slice_dispatch<C, start, count,
        static_cast<int_t>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  template<>
  struct negative_slice_select<false>
  {
    template<int_t start, unsigned count, class C>
    struct impl
    {
      template<class... xs>
      using f = typename positive_slice_dispatch<C, start, count>
        ::template f<sizeof...(xs)>
        ::template f<xs...>;
    };
  };


  template<class C>
  struct positive_slice_impl<C, -1, -1>
  {
    template<int_t /*n*/>
    using f = clear<C>;
  };

  template<class C, int_t i, int_t e>
  struct positive_slice_impl
  {
    template<int_t n, int_t ri = n <= i ? -1 : n < e ? 0 : n - e>
    using f = slice_impl<C, ri == -1 ? -1 : i, ri>;
  };


  template<class C>
  struct slice_impl<C, -1, -1> : clear<C>
  {};

  template<class C, int_t i>
  struct slice_impl<C, i, 0> : drop_front_c<i, C>
  {};

  template<class C>
  struct slice_impl<C, 0, 0> : C
  {};

  template<class C, int_t i, int_t ri>
  struct slice_impl : rotate_c<-ri, drop_front_c<i + ri, C>>
  {};


  template<>
  struct negative_strided_slice_select<true>
  {
    template<int_t start, unsigned count, unsigned step, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_strided_slice_dispatch<start, count, step,
        static_cast<int_t>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >
        ::template impl<C, step, sizeof...(xs)>
        ::template f<xs...>;
    };
  };

  template<>
  struct negative_strided_slice_select<false>
  {
    template<int_t start, unsigned count, unsigned step, class C>
    struct impl
    {
      template<class... xs>
      using f = typename positive_strided_slice_dispatch<start, count, step>
        ::template impl<C, step, sizeof...(xs)>
        ::template f<xs...>;
    };
  };


  template<>
  struct positive_strided_slice_impl<-1, -1>
  {
    // = 0 to be usable in range.hpp
    template<class C, unsigned /*step*/ = 0, int_t /*n*/ = 0>
    using impl = clear<C>;
  };

  template<int_t i, int_t e>
  struct positive_strided_slice_impl
  {
    template<class C, unsigned step, int_t n,
      int_t ri = n <= i ? -1 : n - (n < e ? (n - 1 - i) / step * step + i + 1 : e)>
    using impl = typename strided_slice_impl<ri == -1 ? -1 : i, ri>
      ::template impl<C, step, n>;
  };


  template<>
  struct strided_slice_impl<-1, -1> : positive_strided_slice_impl<-1, -1>
  {};

#if JLN_MP_FAST_TYPE_PACK_ELEMENT
  template<class, int... ints>
  struct slided_slice
  {
    template<class C, int i, int step>
    struct impl : arrange_c_with<C, ints * step + i ...>
    {};
  };

  template<int_t i, int_t ri>
  struct strided_slice_impl
  {
    template<class C, int step, int n>
    using impl =
      typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, (n - i - ri) / step + 1, slided_slice)
      ::template impl<C, i, step>
    ;
  };
#else // !JLN_MP_FAST_TYPE_PACK_ELEMENT
  template<class, unsigned... ints>
  struct slided_slice
  {
    template<class C, unsigned step>
    struct impl : compress_c_with<C, ints % step == 0 ...>
    {};
  };

  template<int_t i>
  struct strided_slice_impl<i, 0>
  {
    template<class C, unsigned step, std::size_t n>
    using impl = drop_front_c<i,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i, slided_slice)
      ::template impl<C, step>
    >;
  };

  template<int_t i, int_t ri>
  struct strided_slice_impl
  {
    template<class C, unsigned step, std::size_t n>
    using impl = rotate_c<-ri, drop_front_c<i + ri,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i - ri, slided_slice)
      ::template impl<C, step>
    >>;
  };
#endif
} // namespace jln::mp::detail
/// \endcond
