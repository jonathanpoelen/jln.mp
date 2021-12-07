#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves an element of a sequence at an arbitrary position.
  /// \pre `0 <= N < sizeof...(xs)`
  /// \treturn \value
  template<class N, class C = identity>
  using at = drop_front<N, front<C>>;

  template<unsigned n, class C = identity>
  using at_c = drop_front_c<n, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop_front_c<1, front<C>>;

  template<class C = identity>
  using at2 = drop_front_c<2, front<C>>;

  template<class C = identity>
  using at3 = drop_front_c<3, front<C>>;

  template<class C = identity>
  using at4 = drop_front_c<4, front<C>>;

  template<class C = identity>
  using at5 = drop_front_c<5, front<C>>;

  template<class C = identity>
  using at6 = drop_front_c<6, front<C>>;

  template<class C = identity>
  using at7 = drop_front_c<7, front<C>>;

  template<class C = identity>
  using at8 = drop_front_c<8, front<C>>;

  template<class C = identity>
  using at9 = drop_front_c<9, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = unpack<L, mp::drop_front_c<i::value, mp::front<C>>>;

    template<class L, unsigned i, class C = mp::identity>
    using at_c = unpack<L, mp::drop_front_c<i, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = unpack<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = unpack<L, mp::drop_front_c<1, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = unpack<L, mp::drop_front_c<2, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = unpack<L, mp::drop_front_c<3, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = unpack<L, mp::drop_front_c<4, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = unpack<L, mp::drop_front_c<5, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = unpack<L, mp::drop_front_c<6, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = unpack<L, mp::drop_front_c<7, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = unpack<L, mp::drop_front_c<8, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = unpack<L, mp::drop_front_c<9, mp::front<C>>>;
  }
}
