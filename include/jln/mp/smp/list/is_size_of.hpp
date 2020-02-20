#pragma once

#include "../functional/identity.hpp"
#include "../../list/is_size_of.hpp"

namespace jln::mp::smp
{
  template<int_ n, class C = identity>
  using is_size_of_c = valid_contract<mp::is_size_of_c<n, subcontract<C>>>;

  template<class C = identity>
  using is_size_of_1 = valid_contract<mp::is_size_of_1<subcontract<C>>>;

  template<class C = identity>
  using is_size_of_2 = valid_contract<mp::is_size_of_2<subcontract<C>>>;

  template<int_ n, class C = identity>
  using is_size_larger_than_c = valid_contract<mp::is_size_larger_than_c<n, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(is_size_of, (N), (C, smp::identity), smp::is_size_of_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(is_size_larger_than, (N), (C, smp::identity),
  smp::is_size_larger_than_c<N::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, is_size_of<N, C>>
  {
    using type = smp::is_size_of<N, sfinae<C>>;
  };
}
