#pragma once

#include "../list/list.hpp"
#include "../../list/slice.hpp"

namespace jln::mp::smp
{
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  // TODO stride == 0 -> bad_contract
  using slice_c = contract<always<number<(stride > 0)>>,
    try_invoke<mp::slice<number<start>, number<size>, number<stride>, subcontract<C>>>>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(slice, (start), (size), (stride, number<1>), (C, smp::listify),
  smp::slice_c<start::value, size::value, stride::value, C>)


namespace jln::mp::detail
{
  template<template<class> class sfinae, class start, class size, class stride, class C>
  struct _sfinae<sfinae, slice<start, size, stride, C>>
  {
    using type = smp::slice<start, size, stride, sfinae<C>>;
  };
}
