#pragma once

#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see take_back_max, take_front, drop_front, drop_back, take_while
  template<class N, class C = listify>
  struct take_back
  {
    template<class... xs>
    using f = typename detail::_drop_front<
      detail::n_8_or_less_16_64_256(
        sizeof...(xs) - detail::validate_index<N::value, sizeof...(xs)>::value
      )
    >::template f<sizeof...(xs) - N::value, C, xs...>;
  };

  /// Extracts at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see take_front, take_back, take_while
  template<class N, class C = listify>
  struct take_back_max
  {
    template<class... xs>
    using f = typename detail::_drop_front<
      detail::n_8_or_less_16_64_256(
        sizeof...(xs) - detail::min(std::size_t{N::value}, sizeof...(xs))
      )
    >::template f<sizeof...(xs) - detail::min(std::size_t{N::value}, sizeof...(xs)), C, xs...>;
  };

  template<int_ n, class C = listify>
  using take_back_c = take_back<number<n>, C>;

  template<int_ n, class C = listify>
  using take_back_max_c = take_back_max<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take_back = unpack<L, mp::take_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_c = unpack<L, mp::take_back<number<n>, C>>;

    template<class L, class N, class C = mp::listify>
    using take_back_max = unpack<L, mp::take_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_back_max_c = unpack<L, mp::take_back_max<number<n>, C>>;
  }

  /// \cond
  template<class C>
  struct take_back<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };

  template<class C>
  struct take_back_max<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };
  /// \endcond
}
