// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/lookup.hpp>
#include <jln/mp/utility/is.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct smp_check_unindexed;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using build_indexed = contract<build_indexed<assume_unary<C>>>;

  template<class Seq, class C = identity>
  using lookup = typename mp::try_contract<mp::lookup<Seq,
    detail::smp_check_unindexed<assume_unary<C>>
  >>;

  template<unsigned i, class C = identity>
  using precomputed_indexes_at_c = try_contract<mp::precomputed_indexes_at_c<i,
    detail::smp_check_unindexed<assume_unary<C>>
  >>;
}

JLN_MP_MAKE_REGULAR_SMP2_P(precomputed_indexes_at, (I), (C, smp::identity),
  smp::precomputed_indexes_at_c<I::value, C>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, build_indexed<C>>
  {
    using type = smp::build_indexed<sfinae<C>>;
  };

  template<template<class> class sfinae, unsigned i, class C>
  struct _sfinae<sfinae, precomputed_indexes_at_c<i, C>>
  {
    using type = smp::precomputed_indexes_at_c<i, sfinae<C>>;
  };

  template<template<class> class sfinae, class Seq, class C>
  struct _sfinae<sfinae, lookup<Seq, C>>
  {
    using type = smp::lookup<Seq, sfinae<C>>;
  };

  template<class x>
  struct smp_check_unindexed_impl
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<>
  struct smp_check_unindexed_impl<unindexed>
  {
    template<class C>
    using f = na;
  };

  template<class C>
  struct smp_check_unindexed
  {
    template<class x>
    using f = typename smp_check_unindexed_impl<x>::template f<C>;
  };
}
/// \endcond
