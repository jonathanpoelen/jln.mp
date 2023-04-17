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
    struct _slice;

    constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride);
  }
  /// \endcond

  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// \pre `0 <= start <= sizeof...(xs)`
  /// \pre `0 < stride`
  /// \pre `0 <= size`
  /// \pre `0 <= (size - 1) * stride + start + 1 <= sizeof...(xs)`
  /// \treturn \sequence
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  struct slice_c
  {
    template<class... xs>
    using f = typename detail::_slice<
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


#include <jln/mp/functional/lift.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <utility>

/// \cond
namespace jln::mp::detail
{
  constexpr unsigned slide_select(unsigned nx, unsigned size, unsigned stride)
  {
    return !size ? 0
      : size == 1 ? 3
      : stride <= 1 ? 2
      : nx < stride ? 2
      : 1;
  }

  template<>
  struct _slice<2>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, int_ len>
    using f = rotate_c<start + size, drop_front_c<len - size, C>>;
  };

#if JLN_MP_MSVC
  template<unsigned size, unsigned stride, unsigned i, class x>
  using slice_impl_msvc = typename wrap_in_list_c<(i <= size && i % stride == 0)>::template f<x>;
#endif

#if JLN_MP_USE_INTEGER_PACK
  template<unsigned size, unsigned stride, class C, unsigned... ints>
  struct _slice_impl
#else
  template<unsigned size, unsigned stride, class C, class>
  struct _slice_impl;

  template<unsigned size, unsigned stride, class C, std::size_t... ints>
  struct _slice_impl<size, stride, C, std::integer_sequence<std::size_t, ints...>>
#endif
  {
    template<class... xs>
    using f = typename join<C>::template f<
#if JLN_MP_MSVC
      slice_impl_msvc<size, stride, ints, xs>...
#else
      typename wrap_in_list_c<(ints <= size && ints % stride == 0)>
      ::template f<xs>...
#endif
    >;
  };

  template<>
  struct _slice<1>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, std::size_t len>
    using f = drop_front_c<
      start,
      _slice_impl<size * stride - stride + 1, stride, C,
        JLN_MP_INTEGER_PACK_OR_STD_MAKE_INDEX_SEQUENCE(len - start)
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, std::size_t len>
    using f = clear<C>;
  };

  template<>
  struct _slice<3>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, std::size_t len>
    using f = drop_front_c<start, front<C>>;
  };
}
/// \endcond
