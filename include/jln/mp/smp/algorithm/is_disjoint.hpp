#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/algorithm/is_disjoint.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Equal>
  struct mk_smp_is_disjoint_with;

  template<class C, class F = listify>
  struct seqs_to_list;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_disjoint = try_contract<detail::seqs_to_list<mp::is_disjoint<assume_number<C>>>>;

  template<class Equal = lift<std::is_same>, class C = identity>
  using is_disjoint_with = typename detail::mk_smp_is_disjoint_with<Equal>
    ::template f<assume_number<C>>;
}


#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/algorithm/drop_while.hpp>
#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Equal, class C>
  struct _sfinae<sfinae, is_disjoint_with<Equal, C>>
  {
    using type = smp::is_disjoint_with<sfinae<Equal>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_disjoint_with<lift<std::is_same>, C>>
  {
    using type = smp::is_disjoint<sfinae<C>>;
  };


  template<class C, class F>
  struct seqs_to_list
  {
    template<class... seqs>
    using f = typename C::template f<typename _unpack<seqs>::template f<F>...>;
  };


  template<class Pred>
  using smp_is_disjoint_impl = smp::drop_while<
    Pred, contract_barrier<mp::always<mp::false_>>, contract_barrier<mp::always<mp::true_>>
  >;

  template<class Equal, class... xs>
  struct smp_is_disjoint_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract_barrier<push_back<x, Equal>>,
      contract_barrier<mp::always<mp::false_>>,
      contract_barrier<mp::always<mp::true_>>
    >::template f<xs...>;
  };

  template<uint_>
  struct smp_is_disjoint_n;

  template<>
  struct smp_is_disjoint_n<0>
  {
    template<class Equal, class... xs>
    using f = true_;
  };

  template<>
  struct smp_is_disjoint_n<1>
  : try_<seqs_to_list<mp::always<true_>, mp::always<true_>>>
  {};

  template<class Equal, class seq0>
  using smp_to_is_disjoint_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract_barrier<lift<smp_is_disjoint_of>>>
    ::template f<seq0, Equal>
  >>;

  template<>
  struct smp_is_disjoint_n<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename smp_to_is_disjoint_impl<Equal, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_disjoint_n<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_disjoint_impl<Equal, seq0>>
      ::template f<seqs...>;
  };

  template<class Equal, class C>
  struct smp_is_disjoint_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_disjoint_n<min(3, sizeof...(seqs))>
      ::template f<Equal, seqs...>
    >;
  };

  template<class Equal>
  struct mk_smp_is_disjoint_with
  {
    template<class C>
    using f = contract<smp_is_disjoint_with<
      smp::concepts::predicate<assume_binary<Equal>, mp::identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_disjoint_with<lift<std::is_same>>
  {
    template<class C>
    using f = smp::is_disjoint<C>;
  };
}
/// \endcond
