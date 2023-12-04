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
    template<class C, int_ i, int_ ri>
    struct slice_impl;

    template<int_ i, int_ ri>
    struct strided_slice_impl;

    template<class C, int_ i, int_ ri>
    struct positive_slice_impl;

    template<int_ i, int_ ri>
    struct positive_strided_slice_impl;

    template<bool>
    struct negative_slice_select;

    template<bool>
    struct negative_strided_slice_select;

    // pre: start < 0
    // pre: count > 0
    // pre: step > 0
    // pre: n >= 0
    template<int_ start, int_ count, int_ step, int_ n,
      int_ i = n + start,
      int_ e = i + (count - 1) * step + 1,
      int_ ii
        = e <= 0
        ? -1
        : i < 0
        ? -i % step
        : i,
      int_ ri
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
    template<int_ i, int_ count, int_ step,
      int_ e = i + (count - 1) * step + 1
    >
    using positive_strided_slice_dispatch = positive_strided_slice_impl<
      e <= 0 ? -1 : i < 0 ? -i % step : i,
      e <= 0 ? -1 : e
    >;

    // pre: start < 0
    // pre: count > 0
    // pre: n >= 0
    template<class C, int_ start, int_ count, int_ n,
      int_ e = n + start + count,
      int_ i
        = e <= 0
        ? -1
        : n < -start
        ? 0
        : n + start,
      int_ ri
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
    template<class C, int_ i, int_ count, int_ e = i + count>
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
  /// \pre `0 < step`
  /// \treturn \sequence
  template<int_ start, unsigned count, unsigned step = 1, class C = listify>
  struct slice_with_step_c
    : detail::negative_strided_slice_select<start < 0>
    ::template impl<start, count, step, C>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class start, class count, class step = number<1>, class C = listify>
  using slice_with_step = slice_with_step_c<start::value, count::value, step::value, C>;

  template<int_ start, unsigned count, class C = listify>
  using slice_c = slice_with_step_c<start, count, 1, C>;

  template<class start, class count, class C = listify>
  using slice = slice_with_step_c<start::value, count::value, 1, C>;

  namespace emp
  {
    template<class L, class start, class count, class step = number<1>, class C = mp::listify>
    using slice_with_step = unpack<L, slice_with_step<start, count, step, C>>;

    template<class L, int_ start, unsigned count, unsigned step = 1, class C = mp::listify>
    using slice_with_step_c = unpack<L, mp::slice_with_step_c<start, count, step, C>>;

    template<class L, class start, class count, class C = mp::listify>
    using slice = unpack<L, mp::slice_with_step_c<start::value, count::value, 1, C>>;

    template<class L, int_ start, unsigned count, class C = mp::listify>
    using slice_c = unpack<L, mp::slice_with_step_c<start, count, 1, C>>;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/join.hpp>

/// \cond
namespace jln::mp
{
  template<int_ start, unsigned count, class C>
  struct slice_with_step_c<start, count, 1, C>
    : detail::negative_slice_select<start < 0>
    ::template impl<start, count, C>
  {};

  template<int_ start, unsigned step, class C>
  struct slice_with_step_c<start, 0, step, C> : clear<C>
  {};

  // invalid
  template<int_ start, unsigned count, class C>
  struct slice_with_step_c<start, count, 0, C>
  {};

  template<int_ start, class C>
  struct slice_with_step_c<start, 0, 0, C> : clear<C>
  {};

  template<int_ start, class C>
  struct slice_with_step_c<start, 0, 1, C> : clear<C>
  {};
}// namespace jln::mp

namespace jln::mp::detail
{
  template<>
  struct negative_slice_select<true>
  {
    template<int_ start, unsigned count, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_slice_dispatch<C, start, count, sizeof...(xs)>
        ::template f<xs...>;
    };
  };

  template<>
  struct negative_slice_select<false>
  {
    template<int_ start, unsigned count, class C>
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
    template<int_ /*n*/>
    using f = clear<C>;
  };

  template<class C, int_ i, int_ e>
  struct positive_slice_impl
  {
    template<int_ n, int_ ri = n <= i ? -1 : n < e ? 0 : n - e>
    using f = slice_impl<C, ri == -1 ? -1 : i, ri>;
  };


  template<class C>
  struct slice_impl<C, -1, -1> : clear<C>
  {};

  template<class C, int_ i>
  struct slice_impl<C, i, 0> : drop_front_c<i, C>
  {};

  template<class C>
  struct slice_impl<C, 0, 0> : C
  {};

  template<class C, int_ i, int_ ri>
  struct slice_impl : rotate_c<-ri, drop_front_c<i + ri, C>>
  {};


  template<>
  struct negative_strided_slice_select<true>
  {
    template<int_ start, unsigned count, unsigned step, class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_strided_slice_dispatch<start, count, step, sizeof...(xs)>
        ::template impl<C, step, sizeof...(xs)>
        ::template f<xs...>;
    };
  };

  template<>
  struct negative_strided_slice_select<false>
  {
    template<int_ start, unsigned count, unsigned step, class C>
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
    template<class C, unsigned /*step*/ = 0, int_ /*n*/ = 0>
    using impl = clear<C>;
  };

  template<int_ i, int_ e>
  struct positive_strided_slice_impl
  {
    template<class C, unsigned step, int_ n,
      int_ ri = n <= i ? -1 : n - (n < e ? (n - 1 - i) / step * step + i + 1 : e)>
    using impl = typename strided_slice_impl<ri == -1 ? -1 : i, ri>
      ::template impl<C, step, n>;
  };


  template<>
  struct strided_slice_impl<-1, -1> : positive_strided_slice_impl<-1, -1>
  {};

  template<class, unsigned... ints>
  struct slided_slice
  {
    template<class C, unsigned step>
    struct impl : _each<join<C>, wrap_in_list_c<ints % step == 0>...>
    {};
  };

  template<int_ i>
  struct strided_slice_impl<i, 0>
  {
    template<class C, unsigned step, std::size_t n>
    using impl = drop_front_c<i,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i, slided_slice)
      ::template impl<C, step>
    >;
  };

  template<int_ i, int_ ri>
  struct strided_slice_impl
  {
    template<class C, unsigned step, std::size_t n>
    using impl = rotate_c<-ri, drop_front_c<i + ri,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i - ri, slided_slice)
      ::template impl<C, step>
    >>;
  };
} // namespace jln::mp::detail
/// \endcond
