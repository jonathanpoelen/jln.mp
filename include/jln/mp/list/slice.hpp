#pragma once

#include "list.hpp"
#include "../number/number.hpp"
#include "../utility/unpack.hpp"

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
  /// \pre 0 \<= start \< sizeof...(xs)
  /// \pre stride \> 0
  /// \pre 0 \<= size * (stride - 1) + 1 \< sizeof...(xs) - start
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
      unsigned{int_(stride::value)-1}+1u,
      C, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = slice<number<start>, number<size>, number<stride>, C>;

  namespace emp
  {
    template<class L, class start, class size, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, size, stride, C>>;

    template<class L, unsigned start, unsigned size, unsigned stride = 1, class C = mp::listify>
    using slice_c = slice<L, number<start>, number<size>, number<stride>, C>;
  }
}


#include "../algorithm/make_int_sequence.hpp"
#include "../functional/function.hpp"
#include "wrap_in_list.hpp"
#include "join.hpp"
#include "drop.hpp"
#include "take.hpp"
#include "front.hpp"

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
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = drop_c<start, take_c<
      detail::validate_index<size - 1u,
        unsigned{int_(len) - start}>::value + 1u,
      C>>;
  };

  template<unsigned size, unsigned stride, class C>
  struct _slice_impl
  {
    template<int_... ints>
    struct impl
    {
      template<class... xs>
      using f = typename join<C>::template f<
        typename wrap_in_list_c<(ints <= size && ints % stride == 0)>
        ::template f<xs>
      ...>;
    };
  };

  template<>
  struct _slice<1>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, unsigned len>
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
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = typename conditional_c<
      bool(detail::validate_index<start, len>::value)
    >::template f<C, C>;
  };

  template<>
  struct _slice<3>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = drop_c<start, front<C>>;
  };
}
/// \endcond
