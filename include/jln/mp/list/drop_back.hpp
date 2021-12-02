#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/drop_front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Removes \c N elements from the end of a \sequence.
  /// \pre `0 <= N <= sizeof...(xs)`
  /// \treturn \sequence
  /// \see drop_back_max, drop_front, take_front, take_back, drop_while
  template<class N, class C = listify>
  struct drop_back
  {
    template<class... xs>
    using f = typename rotate<number<-N::value>, drop_front<N, C>>::template f<xs...>;
  };

  /// Removes at most \c N elements from the end of a \sequence.
  /// \pre `0 <= N`
  /// \treturn \sequence
  /// \see drop_back, drop_front, drop_while
  template<class N, class C = listify>
  struct drop_back_max
  {
    template<class... xs>
    using f = typename rotate<number<-N::value>,
      drop_front<number<detail::min(std::size_t{N::value}, sizeof...(xs))>, C>
    >::template f<xs...>;
  };

  template<int_ n, class C = listify>
  using drop_back_c = drop_back<number<n>, C>;

  template<int_ n, class C = listify>
  using drop_back_max_c = drop_back_max<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop_back = unpack<L, mp::drop_back<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_c = unpack<L, mp::drop_back<number<n>, C>>;

    template<class L, class N, class C = mp::listify>
    using drop_back_max = unpack<L, mp::drop_back_max<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_back_max_c = unpack<L, mp::drop_back_max<number<n>, C>>;
  }

  /// \cond
  template<class C>
  struct drop_back<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class C>
  struct drop_back_max<number<0>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
  /// \endcond
}
