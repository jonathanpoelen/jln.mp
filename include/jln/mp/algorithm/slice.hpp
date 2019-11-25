#pragma once

#include "filter_mask.hpp"
#include "../list/list.hpp"
#include "../number/number.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _slice;
  }

  template<class start, class size, class stride = number<1>, class C = listify>
  struct slice
  {
    template<class... xs>
    using f = typename detail::_slice<
      (size::value ? (stride::value > 1 ? 1 : 2) : 0)>
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
    using slice = eager<L, slice<start, size, stride, C>>;

    template<class L, unsigned start, unsigned size, unsigned stride = 1, class C = mp::listify>
    using slice_c = slice<L, number<start>, number<size>, number<stride>, C>;
  }
}


#include "remove.hpp"
#include "make_int_sequence.hpp"
#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../functional/bind.hpp"

namespace jln::mp::detail
{
  template<>
  struct _slice<2>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, unsigned len>
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
        typename _wrap_if<(ints < size && ints % stride == 0)>
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
        cfv_v<_slice_impl<
          detail::validate_index<size * stride - 1u, len - start>::value,
          stride, C
        >::template impl>
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, unsigned len>
    using f = typename conditional_c<
      bool(detail::validate_index<start, len>::value)
    >::template f<C, C>;
  };
}
