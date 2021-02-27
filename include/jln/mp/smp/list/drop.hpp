#pragma once

#include <jln/mp/smp/list/drop.hpp>
#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/list/drop.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using drop_c = try_contract<mp::drop<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop, (N), (C, smp::listify), smp::drop_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop<N, C>>
  {
    using type = smp::drop<N, sfinae<C>>;
  };
}
/// \endcond
