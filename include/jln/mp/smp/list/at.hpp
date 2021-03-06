#pragma once

#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/at.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using at_c = detail::sfinae<mp::at_c<n, subcontract_barrier<C>>>;

  template<class C = identity>
  using at0 = detail::sfinae<mp::at0<subcontract_barrier<C>>>;

  template<class C = identity>
  using at1 = detail::sfinae<mp::at1<subcontract_barrier<C>>>;

  template<class C = identity>
  using at2 = detail::sfinae<mp::at2<subcontract_barrier<C>>>;

  template<class C = identity>
  using at3 = detail::sfinae<mp::at3<subcontract_barrier<C>>>;

  template<class C = identity>
  using at4 = detail::sfinae<mp::at4<subcontract_barrier<C>>>;

  template<class C = identity>
  using at5 = detail::sfinae<mp::at5<subcontract_barrier<C>>>;

  template<class C = identity>
  using at6 = detail::sfinae<mp::at6<subcontract_barrier<C>>>;

  template<class C = identity>
  using at7 = detail::sfinae<mp::at7<subcontract_barrier<C>>>;

  template<class C = identity>
  using at8 = detail::sfinae<mp::at8<subcontract_barrier<C>>>;

  template<class C = identity>
  using at9 = detail::sfinae<mp::at9<subcontract_barrier<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(at, (N), (C, smp::identity), smp::at_c<N::value, C>)
