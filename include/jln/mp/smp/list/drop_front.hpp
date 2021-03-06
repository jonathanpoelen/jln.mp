#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using drop_front_c = try_contract<mp::drop_front<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_front, (N), (C, smp::listify), smp::drop_front_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop_front<N, C>>
  {
    using type = smp::drop_front<N, sfinae<C>>;
  };
}
/// \endcond
