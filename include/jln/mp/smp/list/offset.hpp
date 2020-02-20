#pragma once

#include "../functional/identity.hpp"
#include "../../functional/try_invoke.hpp"
#include "../../list/offset.hpp"

namespace jln::mp::smp
{
  template <int_ i, class C = identity>
  using offset_c = valid_contract<mp::offset<number<i>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(offset, (N), (C, smp::identity), smp::offset_c<N::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class I, class C>
  struct _sfinae<sfinae, offset<I, C>>
  {
    using type = smp::offset<I, sfinae<C>>;
  };
}
