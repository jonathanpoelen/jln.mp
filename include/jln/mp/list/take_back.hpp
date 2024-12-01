// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/utility/always.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_back_max, take_front, drop_front, drop_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, JLN_MP_TRACE_F(C)::template f, xs...>;
  };

  /// Extracts at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<unsigned N, class C = listify>
  struct take_back_max_c
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N
      >
      ::template f<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N,
        JLN_MP_TRACE_F(C)::template f,
        xs...
      >;
  };

  template<class N, class C = listify>
  using take_back = take_back_c<N::value, C>;

  template<class N, class C = listify>
  using take_back_max = take_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_back = typename detail::_unpack<mp::take_back<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using take_back_c = typename detail::_unpack<mp::take_back_c<n, C>, L>::type;

    template<class L, class N, class C = mp::listify>
    using take_back_max = typename detail::_unpack<mp::take_back_max<N, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using take_back_max_c = typename detail::_unpack<mp::take_back_max_c<n, C>, L>::type;
  }

  /// \cond
  template<class C>
  struct take_back_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct take_back_max_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<>
  struct take_back_c<0, listify>
    : always<list<>>
  {};

  template<>
  struct take_back_max_c<0, listify>
    : always<list<>>
  {};

#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
  template<unsigned N, template<class...> class C>
  struct take_back_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<sizeof...(xs) - N>
      ::template f<sizeof...(xs) - N, C, xs...>;
  };

  template<unsigned N, template<class...> class C>
  struct take_back_max_c<N, lift<C>>
  {
    template<class... xs>
    using f = typename detail::drop_front_impl<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N
      >
      ::template f<
        sizeof...(xs) <= N ? 0 : sizeof...(xs) - N,
        C, xs...
      >;
  };
#endif
  /// \endcond
}
