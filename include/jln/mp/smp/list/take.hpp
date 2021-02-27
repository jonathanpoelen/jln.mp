#pragma once

#include <jln/mp/smp/list//drop.hpp>
#include <jln/mp/smp/algorithm/rotate.hpp>
#include <jln/mp/list/take.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_c = try_contract<mp::take<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take, (N), (C, smp::listify), smp::take_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, take<N, C>>
  {
    using type = smp::take<N, sfinae<C>>;
  };
}
/// \endcond
