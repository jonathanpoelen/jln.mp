#pragma once

#include "drop.hpp"
#include "front.hpp"

namespace jln::mp
{
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
    using at = eager<L, mp::drop<number<i::value>, mp::front<C>>>;

    template<class L, int_ i, class C = mp::identity>
    using at_c = eager<L, mp::drop<number<i>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = eager<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = eager<L, mp::drop<number<1>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = eager<L, mp::drop<number<2>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = eager<L, mp::drop<number<3>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = eager<L, mp::drop<number<4>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = eager<L, mp::drop<number<5>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = eager<L, mp::drop<number<6>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = eager<L, mp::drop<number<7>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = eager<L, mp::drop<number<8>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = eager<L, mp::drop<number<9>, mp::front<C>>>;
  }
}
