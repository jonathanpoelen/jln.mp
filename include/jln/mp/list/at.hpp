#pragma once

#include "drop.hpp"
#include "front.hpp"

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves an element of a sequence at an arbitrary position.
  /// \pre `0 <= N < sizeof...(xs)`
  /// \treturn \value
  template<class N, class C = identity>
  using at = drop<N, front<C>>;

  template<int_ n, class C = identity>
  using at_c = drop<number<n>, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop<number<1>, front<C>>;

  template<class C = identity>
  using at2 = drop<number<2>, front<C>>;

  template<class C = identity>
  using at3 = drop<number<3>, front<C>>;

  template<class C = identity>
  using at4 = drop<number<4>, front<C>>;

  template<class C = identity>
  using at5 = drop<number<5>, front<C>>;

  template<class C = identity>
  using at6 = drop<number<6>, front<C>>;

  template<class C = identity>
  using at7 = drop<number<7>, front<C>>;

  template<class C = identity>
  using at8 = drop<number<8>, front<C>>;

  template<class C = identity>
  using at9 = drop<number<9>, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = unpack<L, mp::drop<number<i::value>, mp::front<C>>>;

    template<class L, int_ i, class C = mp::identity>
    using at_c = unpack<L, mp::drop<number<i>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = unpack<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = unpack<L, mp::drop<number<1>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = unpack<L, mp::drop<number<2>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = unpack<L, mp::drop<number<3>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = unpack<L, mp::drop<number<4>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = unpack<L, mp::drop<number<5>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = unpack<L, mp::drop<number<6>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = unpack<L, mp::drop<number<7>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = unpack<L, mp::drop<number<8>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = unpack<L, mp::drop<number<9>, mp::front<C>>>;
  }
}
