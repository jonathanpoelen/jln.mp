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

    constexpr int_ slide_select(int_ nx, int_ size, int_ stride);
  }
  /// \endcond

  /// \ingroup list

  /// Returns a subset of elements in a \c xs picked at regular intervals in range.
  /// \pre `0 <= start < sizeof...(xs)`
  /// \pre `stride > 0`
  /// \pre `0 <= size * (stride - 1) + 1 < sizeof...(xs) - start`
  /// \treturn \sequence
  template<class start, class size, class stride = number<1>, class C = listify>
  struct slice
  {
    template<class... xs>
    using f = typename detail::_slice<
      detail::slide_select(int_(sizeof...(xs)) - start::value, size::value, stride::value)
    >
    ::template f<
      start::value, size::value,
      // verify that stride is strictly greater than 0
#ifdef _MSC_VER
      emp::conditional_c<(stride::value > 0), stride, void>::value,
#else
      unsigned{int_(stride::value)-1}+1u,
#endif
      C, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<int_ start, int_ size, int_ stride = 1, class C = listify>
  using slice_c = slice<number<start>, number<size>, number<stride>, C>;

  namespace emp
  {
    template<class L, class start, class size, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, size, stride, C>>;

    template<class L, int_ start, int_ size, int_ stride = 1, class C = mp::listify>
    using slice_c = slice<L, number<start>, number<size>, number<stride>, C>;
  }
}


#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop.hpp>
#include <jln/mp/list/take.hpp>
#include <jln/mp/list/front.hpp>

/// \cond
namespace jln::mp::detail
{
  constexpr int_ slide_select(int_ nx, int_ size, int_ stride)
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
    template<int_ start, int_ size, unsigned /*stride*/, class C, std::size_t len>
    using f = drop_c<start, take_c<
      detail::validate_index<size - 1,
#ifdef _MSC_VER
        (start < int_(len) ? int_(len) - start : 0)
#else
        unsigned{len - start}
#endif
      >::value + 1,
      C>>;
  };

  template<int_ size, int_ stride, class C>
  struct _slice_impl
  {
#ifdef _MSC_VER
    template<int_ i, class x>
    using g = typename wrap_in_list_c<(i <= size && i % stride == 0)>::template f<x>;
#endif

    template<int_... ints>
    struct impl
    {
#ifdef _MSC_VER
      template<class... xs>
      using f = call<join<C>, g<ints, xs>...>;
#else
      template<class... xs>
      using f = typename join<C>::template f<
        typename wrap_in_list_c<(ints <= size && ints % stride == 0)>
        ::template f<xs>
      ...>;
#endif
    };
  };

  template<>
  struct _slice<1>
  {
    template<int_ start, int_ size, unsigned stride, class C, std::size_t len>
    using f = drop_c<
      start,
      typename emp::make_int_sequence_v_c<
        detail::validate_index<int_(len) - start, len>::value,
        lift_c<_slice_impl<
          detail::validate_index<size * stride - stride + 1, len - start>::value,
          stride, C
        >::template impl>
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, std::size_t len>
    using f = typename conditional_c<
      bool(detail::validate_index<start, len>::value)
    >::template f<C, C>;
  };

  template<>
  struct _slice<3>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, std::size_t len>
    using f = drop_c<start, front<C>>;
  };
}
/// \endcond
