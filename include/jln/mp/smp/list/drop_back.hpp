#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/drop_back.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp::smp
{
  template<int_ n, class C = listify>
  using drop_back_c = try_contract<mp::drop_back<mp::number<n>, subcontract<C>>>;

  template<int_ n, class C = listify>
  using drop_back_max_c = try_contract<mp::drop_back_max<mp::number<n>, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(drop_back, (N), (C, smp::listify), smp::drop_back_c<N::value, C>)
JLN_MP_MAKE_REGULAR_SMP2_P(drop_back_max, (N), (C, smp::listify), smp::drop_back_max_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop_back<N, C>>
  {
    using type = smp::drop_back<N, sfinae<C>>;
  };

  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, drop_back_max<N, C>>
  {
    using type = smp::drop_back_max<N, sfinae<C>>;
  };
}
/// \endcond
