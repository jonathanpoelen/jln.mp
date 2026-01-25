// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/list/is_size_of.hpp>

namespace jln::mp::smp
{
  template<int_t n, class C = identity>
  using is_size_of_c = contract<mp::is_size_of_c<n, assume_positive_number<C>>>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(is_size_of, (N), (C, smp::identity), smp::is_size_of_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class N, class C>
  struct _sfinae<sfinae, is_size_of<N, C>>
  {
    using type = smp::is_size_of<N, sfinae<C>>;
  };
}
/// \endcond
