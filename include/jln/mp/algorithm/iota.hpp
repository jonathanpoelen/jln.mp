#pragma once

#include "../list/list.hpp"
#include "../number/numbers.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ start, int_ stride, bool inc>
    struct _iota_v_c;
  }
  /// \endcond

  /// \ingroup ints

  /// Generates a sequence of \c int_.
  /// \return \sequence
  /// \see iota
  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::_iota_v_c<start::value, stride::value, (count::value >= 0)>
      ::template f<C, count::value>;
  };

  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::_iota_v_c<start, stride, (count >= 0)>
      ::template f<C, count>;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = iota_v_c<start::value, count::value, stride::value, C>;

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
    using iota_c = iota_v_c<start, count, stride, mp::numbers<C>>;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = iota_v_c<start::value, count::value, stride::value, mp::numbers<C>>;
  }
}

#include "../algorithm/make_int_sequence.hpp"

/// \cond
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
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<count, C>;
  };

  template<int_ start, int_ stride, bool>
  struct _iota_v_c
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<
      (count < 0 ? -count : count),
      detail::_iota<start, (count < 0 ? -stride : stride), C>>;
  };
}
/// \endcond
