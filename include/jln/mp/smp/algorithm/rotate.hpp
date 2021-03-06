#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp::smp
{
  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(rotate, (N), (C, smp::listify), smp::rotate_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, rotate<N, C>>
  {
    using type = smp::rotate<N, sfinae<C>>;
  };
}
/// \endcond
