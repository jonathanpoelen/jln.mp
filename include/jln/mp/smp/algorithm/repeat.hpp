#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/repeat.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using repeat_c = repeat<mp::number<n>, subcontract<C>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(repeat, (N), (C, smp::listify), smp::repeat_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, repeat<N, C>>
  {
    using type = smp::repeat<N, sfinae<C>>;
  };
}
/// \endcond
