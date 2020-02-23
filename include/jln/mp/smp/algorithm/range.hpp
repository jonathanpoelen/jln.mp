#pragma once

#include "../list/list.hpp"
#include "../../algorithm/range.hpp"

namespace jln::mp::smp
{
  template<int_ beg, int_ end, class C = listify>
  using range_c = valid_contract<mp::range_c<
    beg, end, subcontract<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(range, (beg), (end), (C, smp::listify),
  smp::range_c<beg::value, end::value, C>)

namespace jln::mp::detail
{
  template<template<class> class sfinae, class beg, class end, class C>
  struct _sfinae<sfinae, range<beg, end, C>>
  {
    using type = smp::range<beg, end, sfinae<C>>;
  };
}
