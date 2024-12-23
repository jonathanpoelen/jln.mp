// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/repeat.hpp>
#include <type_traits> // std::void_t

/// \cond
namespace jln::mp::detail
{
  template<bool>
  struct mk_repeat;
}
/// \endcond

namespace jln::mp::smp
{
  template<int_t n, class C = listify>
  using repeat_c = typename detail::mk_repeat<n >= 0>
    ::template f<n, C>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(repeat, (N), (C, smp::listify), smp::repeat_c<N::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, unsigned N, class C>
  struct _sfinae<sfinae, repeat_c<N, C>>
  {
    using type = smp::repeat_c<N, sfinae<C>>;
  };

  template<>
  struct mk_repeat<true>
  {
    template<int_t n, class C>
    using f = contract<mp::repeat_c<n, subcontract<C>>>;
  };

  template<>
  struct mk_repeat<false>
  {
    template<int_t i, class C>
    using f = bad_contract;
  };
}
/// \endcond
