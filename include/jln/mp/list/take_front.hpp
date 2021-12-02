#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_front_max, take_back, drop_front, drop_back, take_while
  template<class N, class C = listify>
  struct take_front
  {
    template<class... xs>
    using f = typename rotate<N, drop_front<number<sizeof...(xs) - N::value>, C>>
      ::template f<xs...>;
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<class N, class C = listify>
  struct take_front_max
  {
    template<class... xs>
    using f = typename rotate<N, drop_front_max<number<sizeof...(xs)
                                 - detail::min(sizeof...(xs), std::size_t{N::value})>, C>>
      ::template f<xs...>;
  };

  template<int_ n, class C = listify>
  using take_front_c = take_front<number<n>, C>;

  template<int_ n, class C = listify>
  using take_front_max_c = take_front_max<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_front = unpack<L, mp::take_front<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_c = unpack<L, mp::take_front<number<n>, C>>;

    template<class L, class N, class C = mp::listify>
    using take_front_max = unpack<L, mp::take_front_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_front_max_c = unpack<L, mp::take_front_max<number<n>, C>>;
  }

  /// \cond
  template<class C>
  struct take_front<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C);
  };

  template<class C>
  struct take_front_max<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C);
  };
  /// \endcond
}

