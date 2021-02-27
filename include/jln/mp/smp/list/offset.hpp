#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/list/offset.hpp>

namespace jln::mp::smp
{
  template <int_ i, class C = identity>
  using offset_c = contract<mp::offset<number<i>, assume_unary<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(offset, (N), (C, smp::identity), smp::offset_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class I, class C>
  struct _sfinae<sfinae, offset<I, C>>
  {
    using type = smp::offset<I, sfinae<C>>;
  };
}
/// \endcond
