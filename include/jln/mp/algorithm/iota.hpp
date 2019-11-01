#pragma once

#include "list.hpp"
#include "../number/numbers.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int_ start, int_ stride, bool inc>
    struct _iota_v_c;
  }

  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class size, class stride = number<1>>
    using f = typename detail::_iota_v_c<start::value, stride::value, (size::value >= 0)>
      ::template f<C, size::value>;
  };

  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ size, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::_iota_v_c<start, stride, (size >= 0)>
      ::template f<C, size>;

    template<class start, class size, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = iota_v_c<start::value, size::value, stride::value, C>;

    template<int_ start, int_ size, int_ stride = 1, class C = mp::listify>
    using iota_c = iota_v_c<start, size, stride, mp::numbers<C>>;

    template<class start, class size, class stride = number<1>, class C = mp::listify>
    using iota = iota_v_c<start::value, size::value, stride::value, mp::numbers<C>>;
  }
}

#include "../algorithm/make_int_sequence.hpp"

namespace jln::mp::detail
{
  template<int_ start, int_ stride, class C>
  struct _iota
  {
    template<int_... ns>
    using f = typename C::template f<(start + ns * stride)...>;
  };

  template<int_ start, int_ stride>
  struct _iota<start, stride, numbers<>>
  {
    template<int_... ns>
    using f = list<number<(start + ns * stride)>...>;
  };

  template<>
  struct _iota_v_c<0, 1, true>
  {
    template<class C, int_ size>
    using f = emp::make_int_sequence_v_c<size, C>;
  };

  template<int_ start, int_ stride, bool>
  struct _iota_v_c
  {
    template<class C, int_ size>
    using f = emp::make_int_sequence_v_c<
      (size < 0 ? -size : size),
      detail::_iota<start, (size < 0 ? -stride : stride), C>>;
  };
}
