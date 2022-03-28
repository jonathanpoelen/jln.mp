#pragma once

#include <jln/mp/smp/algorithm/is_disjoint.hpp>
#include <jln/mp/algorithm/is_subset.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Equal>
  struct mk_smp_is_subset_with;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using is_subset = try_contract<detail::seqs_to_list<mp::is_subset<assume_number<C>>>>;

  template<class Equal = lift<std::is_same>, class C = identity>
  using is_subset_with = typename detail::mk_smp_is_subset_with<Equal>
    ::template f<assume_number<C>>;
}


#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
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


  template<class Equal, class... xs>
  struct smp_is_subset_of
  {
    template<class x>
    using f = typename smp::drop_until<
      contract_barrier<push_back<x, Equal>>,
      contract_barrier<mp::always<mp::true_>>,
      contract_barrier<mp::always<mp::false_>>
    >::template f<xs...>;
  };

  template<uint_>
  struct smp_is_subset_n;

  template<>
  struct smp_is_subset_n<0> : smp_is_disjoint_n<0>
  {};

  template<>
  struct smp_is_subset_n<1> : smp_is_disjoint_n<1>
  {};

  template<class Equal, class seq0>
  using smp_to_is_subset_impl = smp::unpack<smp_is_disjoint_impl<
    typename smp::unpack<contract_barrier<lift<smp_is_subset_of>>>
    ::template f<seq0, Equal>
  >>;

  template<>
  struct smp_is_subset_n<2>
  {
    template<class Equal, class seq0, class seq1>
    using f = typename smp_to_is_subset_impl<Equal, seq0>
      ::template f<seq1>;
  };

  template<>
  struct smp_is_subset_n<3>
  {
    template<class Equal, class seq0, class... seqs>
    using f = typename smp_is_disjoint_impl<smp_to_is_subset_impl<Equal, seq0>>
      ::template f<seqs...>;
  };

  template<class Equal, class C>
  struct smp_is_subset_with
  {
    template<class... seqs>
    using f = typename C::template f<
      typename smp_is_subset_n<min(3, sizeof...(seqs))>
      ::template f<Equal, seqs...>
    >;
  };

  template<class Equal>
  struct mk_smp_is_subset_with
  {
    template<class C>
    using f = contract<smp_is_subset_with<
      smp::concepts::predicate<assume_binary<Equal>, mp::identity, violation>, C>>;
  };

  template<>
  struct mk_smp_is_subset_with<lift<std::is_same>>
  {
    template<class C>
    using f = subcontract<smp::is_subset<C>>;
  };
}
/// \endcond
