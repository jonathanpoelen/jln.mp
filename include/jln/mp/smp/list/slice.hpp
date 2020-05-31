#pragma once

#include "../list/listify.hpp"
#include "../../list/slice.hpp"

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct smp_slice_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = typename detail::smp_slice_select<(stride > 0)>
    ::template f<start, size, stride, C>;
}

JLN_MP_MAKE_REGULAR_SMP4_P(slice, (start), (size), (stride, number<1>), (C, smp::listify),
  smp::slice_c<start::value, size::value, stride::value, C>)


/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_slice_select<false>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = bad_contract;
  };

  template<>
  struct smp_slice_select<true>
  {
    template<unsigned start, unsigned size, unsigned stride, class C>
    using f = try_contract<
      mp::slice<number<start>, number<size>, number<stride>,
      subcontract<C>>>;
  };

  template<template<class> class sfinae, class start, class size, class stride, class C>
  struct _sfinae<sfinae, slice<start, size, stride, C>>
  {
    using type = smp::slice<start, size, stride, sfinae<C>>;
  };
}
/// \endcond
