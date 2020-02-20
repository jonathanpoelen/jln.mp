#pragma once

#include "drop.hpp"
#include "front.hpp"
#include "../functional/identity.hpp"
#include "../../list/at.hpp"

namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using at_c = detail::sfinae<mp::at_c<n, C>>;

  template<class C = identity>
  using at0 = detail::sfinae<mp::at0<C>>;

  template<class C = identity>
  using at1 = detail::sfinae<mp::at1<C>>;

  template<class C = identity>
  using at2 = detail::sfinae<mp::at2<C>>;

  template<class C = identity>
  using at3 = detail::sfinae<mp::at3<C>>;

  template<class C = identity>
  using at4 = detail::sfinae<mp::at4<C>>;

  template<class C = identity>
  using at5 = detail::sfinae<mp::at5<C>>;

  template<class C = identity>
  using at6 = detail::sfinae<mp::at6<C>>;

  template<class C = identity>
  using at7 = detail::sfinae<mp::at7<C>>;

  template<class C = identity>
  using at8 = detail::sfinae<mp::at8<C>>;

  template<class C = identity>
  using at9 = detail::sfinae<mp::at9<C>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(at, (N), (C, smp::identity), smp::at_c<N::value, C>)
