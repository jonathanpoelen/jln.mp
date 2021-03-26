#pragma once

#include <jln/mp/smp/algorithm/is_disjoint.hpp>
#include <jln/mp/algorithm/is_subset.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Equal, class C>
  struct smp_is_subset_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_subset = try_contract<detail::seqs_to_list<mp::is_subset<assume_number<C>>>>;

  template<class Equal = lift<std::is_same>, class C = identity>
  using is_subset_with = contract<
    detail::smp_is_subset_with<assume_binary<Equal>, assume_number<C>>
  >;
}


/// \cond
namespace jln::mp::detail
{
  template<class NotEqual, class... xs>
  struct smp_is_subset_of
  {
    template<class x>
    using f = number<!smp_is_disjoint_impl<contract_barrier<
      push_back<x, NotEqual>
    >>::template f<xs...>::value>;
  };

  template<uint_>
  struct smp_is_subset_n;

  template<>
  struct smp_is_subset_n<0>
  {
    template<class NotEqual, class... xs>
    using f = true_;
  };

  template<>
  struct smp_is_subset_n<1>
  : try_<seqs_to_list<mp::always<true_>, mp::always<true_>>>
  {};

  template<class NotEqual, class seq0>
  using smp_to_is_subset_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract_barrier<if_<
      size<>,
      lift<smp_is_subset_of>,
      always<size<not_<>>>
    >>>
    ::template f<seq0, NotEqual>
  >>;

  template<>
  struct smp_is_subset_n<2>
  {
    template<class NotEqual, class seq0, class seq1>
    using f = typename smp_to_is_subset_impl<NotEqual, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_subset_n<3>
  {
    template<class NotEqual, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_subset_impl<NotEqual, seq0>>
      ::template f<seqs...>;
  };

  template<class Equal, class C>
  struct smp_is_subset_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_subset_n<min(3, sizeof...(seqs))>
      ::template f<to_predicate_not_t<Equal>, seqs...>
    >;
  };

  template<class C>
  struct smp_is_subset_with<lift<std::is_same>, C>
  : subcontract<smp::is_subset<C>>
  {};


  template<template<class> class sfinae, class Equal, class C>
  struct _sfinae<sfinae, is_subset_with<Equal, C>>
  {
    using type = smp::is_subset_with<sfinae<Equal>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_subset_with<lift<std::is_same>, C>>
  {
    using type = smp::is_subset<sfinae<C>>;
  };
}
/// \endcond
