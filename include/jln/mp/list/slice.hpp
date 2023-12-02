// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct slice_impl;

    constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride);
  }
  /// \endcond

  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// \pre `0 <= start <= sizeof...(xs)`
  /// \pre `0 < stride`
  /// \pre `0 <= (size - 1) * stride + start + 1 <= sizeof...(xs)`
  /// \treturn \sequence
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  struct slice_c
  {
    template<class... xs>
    using f = typename detail::slice_impl<
      detail::slide_select(sizeof...(xs) - start, size, stride)
    >
    ::template f<start, size, stride, C, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<class start, class size, class stride = number<1>, class C = listify>
  using slice = slice_c<start::value, size::value, stride::value, C>;

  namespace emp
  {
    template<class L, class start, class size, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, size, stride, C>>;

    template<class L, unsigned start, unsigned size, unsigned stride = 1, class C = mp::listify>
    using slice_c = unpack<L, slice_c<start, size, stride, C>>;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/clear.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride)
  {
    return size <= 1 ? size
      : stride <= 1 ? 2
      : nx < stride ? 2
      : 3;
  }

  // size = 0
  template<>
  struct slice_impl<0>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, std::size_t len>
    using f = clear<C>;
  };

  // size = 1
  template<>
  struct slice_impl<1>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, std::size_t len>
    using f = drop_front_c<start, front<C>>;
  };

  // stride <= 1 || sizeof...(xs) < stride + start
  template<>
  struct slice_impl<2>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, int_ len>
    using f = rotate_c<start + size, drop_front_c<len - size, C>>;
  };

  template<class, unsigned... ints>
  struct slided_slice
  {
    template<class C, unsigned stride>
    struct impl : _each<join<C>, wrap_in_list_c<ints % stride == 0>...>
    {};
  };

  // other
  template<>
  struct slice_impl<3>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, std::size_t len,
      unsigned range_size = stride * (size - 1) + 1>
    using f = rotate_c<range_size + start,
      drop_front_c<len - range_size,
        typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(unsigned, range_size, slided_slice)
          ::template impl<C, stride>
      >
    >;
  };
}
/// \endcond
