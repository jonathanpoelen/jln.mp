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
  /// \pre `0 <= start <= sizeof...(xs)`
  /// \pre `0 < stride`
  /// \pre `0 <= size`
  /// \pre `0 <= (size - 1) * stride + start + 1 <= sizeof...(xs)`
  /// \treturn \sequence
  template<class start, class size, class stride = number<1>, class C = listify>
  struct slice
  {
    template<class... xs>
    using f = typename detail::_slice<
      detail::slide_select(int_(sizeof...(xs)) - start::value, size::value, stride::value)
    >
    ::template f<start::value, size::value, stride::value, C, sizeof...(xs)>
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
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/clear.hpp>

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
    using f = drop_front_c<start, take_front_c<size, C>>;
  };

  template<int_ size, int_ stride, class C>
  struct _slice_impl
  {
#if JLN_MP_MSVC
    template<int_ i, class x>
    using g = typename wrap_in_list_c<(i <= size && i % stride == 0)>::template f<x>;
#endif

    template<int_... ints>
    struct impl
    {
#if JLN_MP_MSVC
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
    using f = drop_front_c<
      start,
      typename emp::make_int_sequence_v_c<
        len - start,
        lift_c<_slice_impl<size * stride - stride + 1, stride, C>
               ::template impl>
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, std::size_t len>
    using f = clear<C>;
  };

  template<>
  struct _slice<3>
  {
    template<int_ start, int_ size, unsigned /*stride*/, class C, std::size_t len>
    using f = drop_front_c<start, front<C>>;
  };
}
/// \endcond
