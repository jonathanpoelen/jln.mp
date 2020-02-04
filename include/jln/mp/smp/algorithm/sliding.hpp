#pragma once

#include "../../algorithm/sliding.hpp"
#include "../list/list.hpp"

namespace jln::mp::smp
{
  template<class size, class stride = mp::number<1>, class C = listify>
  using sliding = try_contract<mp::sliding<size, stride, subcontract<C>>>;

  template<int_ size, int_ stride = 1, class C = listify>
  using sliding_c = try_contract<mp::sliding_c<size, stride, subcontract<C>>>;
}

namespace jln::mp::detail
{
  template<class C>
  using smp_sliding_nostride = try_contract<sliding_nostride<subcontract<C>>>;

  template<class C>
  using smp_sliding_0size = try_contract<sliding_0size<subcontract<C>>>;

  template<template<class> class sfinae, int_ size, int_ stride, class C>
  struct _sfinae<sfinae, sliding_<size, stride, C>>
  {
    using type = smp::sliding_c<size, stride, sfinae<C>>;
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
