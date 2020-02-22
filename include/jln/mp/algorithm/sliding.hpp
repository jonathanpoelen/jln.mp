#pragma once

#include "transform.hpp"
#include "../number/number.hpp"
#include "../config/enumerate.hpp"
#include "../list/list.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  namespace detail
  {
    constexpr int_ sliding_stride(int_ size, int_ stride);

    template<int_ size, int_ stride, int_ = sliding_stride(size, stride)>
    struct mk_sliding;
  }

  template<class size, class stride = number<1>, class C = listify>
  using sliding = typename detail::mk_sliding<size::value, stride::value>::template f<C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using sliding_c = typename detail::mk_sliding<size, stride>::template f<C>;

  namespace emp
  {
    template<class L, class size, class stride = number<1>, class C = mp::listify>
    using sliding = eager<L, mp::sliding<size, stride, C>>;

    template<class L, int_ size, int_ stride = 1, class C = mp::listify>
    using sliding_c = eager<L, mp::sliding_c<size, stride, C>>;
  }
}


#include "zip.hpp"
#include "make_int_sequence.hpp"
#include "rotate.hpp"
#include "transform.hpp"
#include "group_n.hpp"
#include "slice.hpp"
#include "../functional/fork.hpp"
#include "../list/drop.hpp"

namespace jln::mp::detail
{
  constexpr int_ sliding_stride(int_ size, int_ stride)
  {
    if (!stride || size < 1) {
      return size == 0 ? -2 : -1;
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
  struct _sliding;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::_sliding<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, size, stride, xs...>;
  };

  // TODO also with zip
  template<class C>
  struct optimize_with_pattern
  {
    using type = C;
  };

  template<class C>
  struct optimize_with_pattern<transform<unpack<listify>, C>>
  : optimize_with_pattern<C>
  {};

  template<int_ size, int_, int_ stride>
  struct mk_sliding
  {
    template<class C>
    using f = sliding_<size, stride, typename optimize_with_pattern<C>::type>;
  };

  // TODO generic class for error
  template<class C>
  struct sliding_nostride
  {};

  template<class C>
  struct sliding_0size
  {
    template<class... xs>
    using f = typename dcall<sizeof...(xs) < 100000>::template f<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -1>
  {
    template<class C>
    using f = sliding_nostride<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -2>
  {
    template<class C>
    using f = sliding_0size<C>;
  };

  constexpr int_ slinding_pivot(int_ nx, int_ size, int_ stride)
  {
    int_ r = nx - (nx - size + stride - 1) / stride * stride - 1;
    return r;
  }


  constexpr int sliding_select(int n, int_ size, int_ stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : size == 1 ? (stride == 1 ? 2 : 3)  // C<list<xs>...> / slice<0, n/stride, stride>
      : stride > n ? 9                     // take
      : stride == 1 ? (size == 2 ? 4 : 5)  // common case
      : stride == size ? 6                 // group_n
      // slice<zip_longest> / slice<zip>
      : ((n - size) % stride) ? (slinding_pivot(n, size, stride)  < 0  ?  7 : 8) : 7;
  }

  template<>
  struct _sliding<-1>
  {};

  template<>
  struct _sliding<0>
  {
    template<class C, int_, int_, class...>
    using f = typename C::template f<>;
  };

  template<>
  struct _sliding<1>
  {
    template<class C, int_, int_, class... xs>
    using f = typename C::template f<list<xs...>>;
  };

  template<>
  struct _sliding<2>
  {
    template<class C, int_, int_, class... xs>
    using f = typename C::template f<list<xs>...>;
  };

  template<>
  struct _sliding<3>
  {
    template<class C, int_, int_ stride, class... xs>
    using f = typename _slice<1>
      ::template f<0, (sizeof...(xs) + stride - 1) / stride, stride, transform<listify, C>, sizeof...(xs)>
      ::template f<xs...>;
  };

  template<>
  struct _sliding<4>
  {
    template<class C, int_, int_, class x, class... xs>
    using f = typename _zip_impl<
      C,
      mp::rotate_c<-1, drop_c<1>>::f<x, xs...>,
      list<xs...>
    >::type;
  };

  template<>
  struct _sliding<5>
  {
    template<class C, int_ size, class drop>
    struct impl
    {
      template<int_... i>
      using f = fork<rotate_c<i-size, drop>..., zip<C>>;
    };

    template<class C, int_ size, int_, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<C, size-1, drop_c<size-1>>>,
      number<size>
    >::template f<xs...>;
  };

  template<>
  struct _sliding<6>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), cfe_c<_group_n_impl>
    >::template f<C, size, xs...>;
  };

  template<>
  struct _sliding<7>
  {
    template<class C, int_ size, int_ stride>
    struct impl
    {
      template<size_t... i>
      using f = fork<slice_c<i, size, stride>..., zip<C>>;
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<C, (sizeof...(xs) - size) / stride + 1, stride>>,
      number<size>
    >::template f<xs...>;
  };

  constexpr int_ slinding8_pivot(int_ nx, int_ size, int_ stride)
  {
    // if (stride >= size) {
    //   return nx - ((nx + stride - 1) / stride - 1) * stride - 1;
    // }
    int_ r = nx - (nx - size + stride - 1) / stride * stride - 1;
    // TODO return 0 + see slinding_pivot
    return r < 0 ? size : r;
  }

  template<>
  struct _sliding<8>
  {
    template<class F, class C>
    struct adjust
    {
      template<class x, class... xs>
      using f = typename C::template f<xs..., typename F::template f<x>>;
    };

    template<class C, int_ size, int_ stride, int_ pivot>
    struct impl
    {
      template<int_... i>
      using f = fork<slice_c<i, size - (pivot < i), stride,
        typename conditional_c<(pivot < i)>::template f<push_back<void>, listify>
      >..., zip<
        rotate_c<-1, adjust<unpack<rotate_c<-1, pop_front<>>>, C>>
      >>;
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<
        C,
        (sizeof...(xs) - size) / stride + 2 /*- (stride > size)*/,
        stride,
        // len - (len - size + stride - 1) / stride * stride
        slinding8_pivot(sizeof...(xs), size, stride)
        // (sizeof...(xs) - size) % stride
      >>,
      number<size>
    >::template f<xs...>;
  };

  template<>
  struct _sliding<9>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename C::template f<typename take_c<size>::template f<xs...>>;
  };
}