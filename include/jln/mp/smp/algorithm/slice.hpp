#pragma once

#include "../list/list.hpp"
#include "../../algorithm/slice.hpp"

namespace jln::mp::smp
{
  template<class start, class size, class stride = number<1>, class C = listify>
  using slice = contract<always<number<(stride::value > 0)>>,
    try_invoke<mp::slice<start, size, stride, subcontract<C>>>>;

  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = slice<number<start>, number<size>, number<stride>, C>;
}


namespace jln::mp::detail
{
  template<template<class> class sfinae, class start, class size, class stride, class C>
  struct _sfinae<sfinae, slice<start, size, stride, C>>
  {
    using type = smp::slice<start, size, stride, sfinae<C>>;
  };
}
