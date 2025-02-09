// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/is_disjoint.hpp>
#include <jln/mp/algorithm/is_subset.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct mk_smp_is_subset_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_subset = try_contract<detail::seqs_to_list<mp::is_subset<assume_positive_number<C>>>>;

  template<class Cmp = same<>, class C = identity>
  using is_subset_with = typename detail::mk_smp_is_subset_with<assume_binary<Cmp>>
    ::template f<assume_positive_number<C>>;
}


#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_subset_with<Cmp, C>>
  {
    using type = smp::is_subset_with<sfinae<Cmp>, sfinae<C>>;
  };


  template<class Cmp, class... xs>
  struct smp_is_subset_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract<push_back<x, Cmp>>,
      contract<always<true_>>,
      contract<always<false_>>
    >::template f<xs...>;
  };

  template<uint_t>
  struct smp_is_subset_select;

  template<>
  struct smp_is_subset_select<0> : smp_is_disjoint_select<0>
  {};

  template<>
  struct smp_is_subset_select<1> : smp_is_disjoint_select<1>
  {};

  template<class Cmp, class seq0>
  using smp_to_is_subset_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract<cfe<smp_is_subset_of>>>
    ::template f<seq0, Cmp>
  >>;

  template<>
  struct smp_is_subset_select<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename smp_to_is_subset_impl<Cmp, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_subset_select<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_subset_impl<Cmp, seq0>>
      ::template f<seqs...>;
  };

  template<class Cmp, class C>
  struct smp_is_subset_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_subset_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<Cmp, seqs...>
    >;
  };

  template<class Cmp>
  struct mk_smp_is_subset_with
  {
    template<class C>
    using f = contract<smp_is_subset_with<
      smp::concepts::predicate<Cmp, mp::identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_subset_with<same<>>
  {
    template<class C>
    using f = smp::is_subset<contract<C>>;
  };
}
/// \endcond
