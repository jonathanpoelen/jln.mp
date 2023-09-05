// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/numbers.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ start, int_ stride, bool inc>
    struct iota_v_c;
  }
  /// \endcond

  /// \ingroup number

  /// Generates a sequence of \int_.
  /// \treturn \sequence of \int_
  /// \see iota
  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::iota_v_c<start::value, stride::value, (count::value >= 0)>
      ::template f<C, count::value>;
  };

  /// \ingroup number

  /// Generates a sequence of \number.
  /// \treturn \sequence of number
  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::iota_v_c<start, stride, (count >= 0)>
      ::template f<C, count>;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = iota_v_c<start::value, count::value, stride::value, C>;

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
    using iota_c = iota_v_c<start, count, stride, mp::numbers<C>>;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = iota_v_c<start::value, count::value, stride::value, mp::numbers<C>>;
  }
}

#include <jln/mp/algorithm/make_int_sequence.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_ start, int_ stride, class C>
  struct iota_impl
  {
    template<class, int_... ns>
    using f = typename conditional_c<sizeof...(ns) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(C), detail::too_many_arguments_error>
      ::template f<(start + ns * stride)...>;
  };

  template<int_ start, int_ stride>
  struct iota_impl<start, stride, numbers<>>
  {
    template<class, int_... ns>
    using f = list<number<(start + ns * stride)>...>;
  };

  template<>
  struct iota_v_c<0, 1, true>
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<count, C>;
  };

  template<int_ start, int_ stride, bool>
  struct iota_v_c
  {
    template<class C, int_ count>
    using f = JLN_MP_D_MAKE_INTEGER_SEQUENCE(
      count < 0 ? -count : count,
      detail::iota_impl<start, count < 0 ? -stride : stride, C>::template f
    );
  };
}
/// \endcond
