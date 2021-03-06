#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/take_back.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using take_back_c = try_contract<mp::take_back<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(take_back, (N), (C, smp::listify), smp::take_back_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, take_back<N, C>>
  {
    using type = smp::take_back<N, sfinae<C>>;
  };
}
/// \endcond
