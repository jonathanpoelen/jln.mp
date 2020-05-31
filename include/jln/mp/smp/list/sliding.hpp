#pragma once

#include "../list/listify.hpp"
#include "../../list/sliding.hpp"

namespace jln::mp::smp
{
  template<int_ size, class C = listify>
  using sliding_c = try_contract<mp::sliding_c<size, subcontract<C>>>;

  template<int_ size, int_ stride, class C = listify>
  using sliding_with_stride_c = try_contract<
    mp::sliding_with_stride_c<size, stride, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(sliding, (size), (C, smp::listify),
  smp::sliding_c<size::value, C>)

JLN_MP_MAKE_REGULAR_SMP3_P(sliding_with_stride, (size), (stride), (C, smp::listify),
  smp::sliding_with_stride_c<size::value, stride::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<class C>
  using smp_sliding_nostride = try_contract<sliding_nostride<subcontract<C>>>;

  template<class C>
  using smp_sliding_0size = try_contract<sliding_0size<subcontract<C>>>;

  template<template<class> class sfinae, int_ size, int_ stride, class C>
  struct _sfinae<sfinae, sliding_<size, stride, C>>
  {
    using type = smp::sliding_with_stride_c<size, stride, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sliding_nostride<C>>
  {
    using type = smp_sliding_nostride<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sliding_0size<C>>
  {
    using type = smp_sliding_0size<sfinae<C>>;
  };
}
/// \endcond
