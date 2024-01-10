// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/is_disjoint.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct mk_smp_is_disjoint_with;

  template<class C, class F = listify>
  struct seqs_to_list;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_disjoint = try_contract<detail::seqs_to_list<mp::is_disjoint<assume_positive_number<C>>>>;

  template<class Cmp = same<>, class C = identity>
  using is_disjoint_with = typename detail::mk_smp_is_disjoint_with<assume_binary<Cmp>>
    ::template f<assume_positive_number<C>>;
}


#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_disjoint_with<Cmp, C>>
  {
    using type = smp::is_disjoint_with<sfinae<Cmp>, sfinae<C>>;
  };


  template<class C, class F>
  struct seqs_to_list
  {
    template<class... seqs>
    using f = typename C::template f<typename _unpack<F, seqs>::type...>;
  };


  template<class Pred>
  using smp_is_disjoint_impl = smp::drop_while<
    Pred, contract<always<false_>>, contract<always<true_>>
  >;

  template<class Cmp, class... xs>
  struct smp_is_disjoint_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract<push_back<x, Cmp>>,
      contract<always<false_>>,
      contract<always<true_>>
    >::template f<xs...>;
  };

  template<uint_>
  struct smp_is_disjoint_select;

  template<>
  struct smp_is_disjoint_select<0>
  {
    template<class Cmp, class... xs>
    using f = true_;
  };

  template<>
  struct smp_is_disjoint_select<1>
  : try_<seqs_to_list<always<true_>, always<true_>>>
  {};

  template<class Cmp, class seq0>
  using smp_to_is_disjoint_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract<lift<smp_is_disjoint_of>>>
    ::template f<seq0, Cmp>
  >>;

  template<>
  struct smp_is_disjoint_select<2>
  {
    template<class Cmp, class seq0, class seq1>
    using f = typename smp_to_is_disjoint_impl<Cmp, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_disjoint_select<3>
  {
    template<class Cmp, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_disjoint_impl<Cmp, seq0>>
      ::template f<seqs...>;
  };

  template<class Cmp, class C>
  struct smp_is_disjoint_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_disjoint_select<sizeof...(seqs) < 3 ? sizeof...(seqs) : 3>
      ::template f<Cmp, seqs...>
    >;
  };

  template<class Cmp>
  struct mk_smp_is_disjoint_with
  {
    template<class C>
    using f = contract<smp_is_disjoint_with<
      smp::concepts::predicate<Cmp, identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_disjoint_with<same<>>
  {
    template<class C>
    using f = smp::is_disjoint<contract<C>>;
  };
}
/// \endcond
