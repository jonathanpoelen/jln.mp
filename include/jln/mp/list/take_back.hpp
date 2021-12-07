#pragma once

#include <jln/mp/list/drop_front.hpp>

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
    using f = typename detail::drop_front_impl<
      sizeof...(xs) - N
    >::template f<sizeof...(xs) - N, C, xs...>;
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
      sizeof...(xs) - detail::min(N, sizeof...(xs))
    >::template f<sizeof...(xs) - detail::min(N, sizeof...(xs)), C, xs...>;
  };

  template<class N, class C = listify>
  using take_back = take_back_c<N::value, C>;

  template<class N, class C = listify>
  using take_back_max = take_back_max_c<N::value, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_back = unpack<L, mp::take_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_c = unpack<L, mp::take_back_c<n, C>>;

    template<class L, class N, class C = mp::listify>
    using take_back_max = unpack<L, mp::take_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_max_c = unpack<L, mp::take_back_max_c<n, C>>;
  }

  /// \cond
  template<class C>
  struct take_back_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };

  template<class C>
  struct take_back_max_c<0, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS_0(xs, C);
  };
  /// \endcond
}
