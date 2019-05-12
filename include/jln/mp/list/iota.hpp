#pragma once

#include "enumerate.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class continuation = listify>
    struct _iota_v_c;
  }

  template<class continuation>
  struct iota
  {
    template<class start, class size, class stride = number<1>>
    using f = typename detail::_iota_v_c<continuation>::template f<start::value, size::value, stride::value>;
  };

  namespace eager
  {
    template<int_ start, int_ size, int_ stride = 1, class continuation = listify>
    using iota_c = typename detail::_iota_v_c<continuation>::template f<start, size, stride>;

    template<class start, class size, class stride = number<1>, class continuation = listify>
    using iota = typename detail::_iota_v_c<continuation>::template f<start::value, size::value, stride::value>;
  }
}

namespace jln::mp::detail
{
  template<int_ start, int_ stride, class continuation>
  struct _iota
  {
    template<int_... ns>
    using f = typename continuation::template f<number<(start + ns * stride)>...>;
  };

  template<class continuation>
  struct _iota_v_c
  {
    template<int_ start, int_ size, int_ stride = 1>
    using f = _enumerate_v_c<
      (size < 0 ? -size : size),
      detail::_iota<start, (size < 0 ? -stride : stride), continuation>>;
  };
}
