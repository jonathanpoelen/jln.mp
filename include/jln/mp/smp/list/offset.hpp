#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/list/offset.hpp>

namespace jln::mp::smp
{
  template <int_ i, class C = identity>
  using offset_c = contract<mp::offset_c<i, assume_number<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(offset, (N), (C, smp::identity), smp::offset_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, int_ I, class C>
  struct _sfinae<sfinae, offset_c<I, C>>
  {
    using type = smp::offset_c<I, sfinae<C>>;
  };
}
/// \endcond
