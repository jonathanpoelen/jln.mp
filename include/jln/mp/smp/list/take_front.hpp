#pragma once

#include <jln/mp/smp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_front_c = try_contract<mp::take_front<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_front, (N), (C, smp::listify), smp::take_front_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, take_front<N, C>>
  {
    using type = smp::take_front<N, sfinae<C>>;
  };
}
/// \endcond
