#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Extracts \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  template<class N, class C = listify>
  struct take_front
  {
    template<class... xs>
    using f = call<
      rotate<N, drop_front<number<sizeof...(xs) - N::value>, C>>,
      xs...>;
  };

  /// Extracts at most \c N elements from the beginning of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  template<class N, class C = listify>
  struct take_front_max
  {
    template<class... xs>
    using f = call<
      rotate<N, drop_front_max<number<sizeof...(xs)
        - detail::min(sizeof...(xs), std::size_t{N::value})>, C>>,
      xs...>;
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
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };

  template<class C>
  struct take_front<number<1>, C>
  {
    template<class _1, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, _1);
  };

  template<class C>
  struct take_front<number<2>, C>
  {
    template<class _1, class _2, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, _1, _2);
  };

  template<class C>
  struct take_front<number<3>, C>
  {
    template<class _1, class _2, class _3, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, _1, _2, _3);
  };

  template<class C>
  struct take_front<number<4>, C>
  {
    template<class _1, class _2, class _3, class _4, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, _1, _2, _3, _4);
  };

  template<class C>
  struct take_front<number<5>, C>
  {
    template<class _1, class _2, class _3, class _4, class _5, class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C, _1, _2, _3, _4, _5);
  };

  template<class C>
  struct take_front_max<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(sizeof...(xs) >= 0, C);
  };
  /// \endcond
}

