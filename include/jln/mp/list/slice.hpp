// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ i, int_ ri, bool long_stride>
    struct slice_impl;

    // pre: count > 0
    // pre: step > 0
    // pre: n >= 0
    template<int_ start, int_ count, int_ step, int_ n,
      int_ i = start < 0 ? n + start : start,
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
    using strided_slice_select = slice_impl<
      ri == -1 ? -1 : ii,
      ri,
      1 < step
    >;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// A negative start represents an index starting from the end.
  /// \pre `0 < step`
  /// \treturn \sequence
  template<int_ start, unsigned count, unsigned step = 1, class C = listify>
  struct slice_c
  {
    template<class... xs>
    using f = typename detail::strided_slice_select<start, count, step, sizeof...(xs)>
      ::template f<C, step, sizeof...(xs)>
      ::template f<xs...>;
  };

  template<class start, class count, class stride = number<1>, class C = listify>
  using slice = slice_c<start::value, count::value, stride::value, C>;

  namespace emp
  {
    template<class L, class start, class count, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, count, stride, C>>;

    template<class L, int_ start, unsigned count, unsigned stride = 1, class C = mp::listify>
    using slice_c = unpack<L, slice_c<start, count, stride, C>>;
  }


  /// \cond
  template<int_ start, unsigned step, class C>
  struct slice_c<start, 0, step, C> : clear<C>
  {};

  // invalid
  template<int_ start, unsigned count, class C>
  struct slice_c<start, count, 0, C>
  {};

  template<int_ start, class C>
  struct slice_c<start, 0, 0, C> : clear<C>
  {};
  /// \endcond
}


#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct slice_impl<-1, -1, false>
  {
    template<class C, unsigned step, std::size_t n>
    using f = clear<C>;
  };

  template<int_ i>
  struct slice_impl<i, 0, false>
  {
    template<class C, unsigned step, std::size_t n>
    using f = drop_front_c<i, C>;
  };

  template<>
  struct slice_impl<0, 0, false>
  {
    template<class C, unsigned step, std::size_t n>
    using f = C;
  };

  template<int_ i, int_ ri>
  struct slice_impl<i, ri, false>
  {
    template<class C, unsigned step, std::size_t n>
    using f = rotate_c<-ri, drop_front_c<i + ri, C>>;
  };

  template<>
  struct slice_impl<-1, -1, true>
  {
    template<class C, unsigned step, std::size_t n>
    using f = clear<C>;
  };

  template<class, unsigned... ints>
  struct slided_slice
  {
    template<class C, unsigned stride>
    struct impl : _each<join<C>, wrap_in_list_c<ints % stride == 0>...>
    {};
  };

  template<int_ i>
  struct slice_impl<i, 0, true>
  {
    template<class C, unsigned step, std::size_t n>
    using f = drop_front_c<i,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i, slided_slice)
      ::template impl<C, step>
    >;
  };

  template<int_ i, int_ ri>
  struct slice_impl<i, ri, true>
  {
    template<class C, unsigned step, std::size_t n>
    using f = rotate_c<-ri, drop_front_c<i + ri,
      typename JLN_MP_MAKE_UNSIGNED_SEQUENCE(n - i - ri, slided_slice)
      ::template impl<C, step>
    >>;
  };
}
/// \endcond
