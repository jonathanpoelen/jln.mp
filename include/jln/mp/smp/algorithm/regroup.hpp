#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/counter.hpp>
#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/smp/functional/invoke_twice.hpp>
#include <jln/mp/smp/functional/lift.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/regroup.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C, class F, class Cmp>
  struct smp_regroup_if_impl;

  template<class Cmp>
  struct smp_regroup_if_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = listify>
  using regroup = contract<mp::regroup<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using regroup_with = contract<mp::counter_wrapped_with<
    mp::if_<
      mp::size<mp::is<mp::number<2>>>,
      detail::counter_to_repeat<assume_unary_or_more<F>>,
      violation
    >,
    detail::smp_listify_or_monadic_xs<F, C>>
  >;

  template<class Cmp = contract<mp::lift<std::is_same>>, class F = listify, class C = listify>
  using regroup_if_with = typename detail::smp_regroup_if_select<Cmp>::template f<C, F>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using regroup_if = regroup_if_with<Cmp, listify, C>;
}

#include <jln/mp/smp/algorithm/copy.hpp>
#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/smp/list/push_front.hpp>
#include <jln/mp/functional/tee.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, regroup<C>>
  {
    using type = smp::regroup<sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, regroup_with<F, C>>
  {
    using type = smp::regroup_with<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class F, class C>
  struct _sfinae<sfinae, regroup_if_with<Cmp, F, C>>
  {
    using type = smp::regroup_if_with<sfinae<Cmp>, sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, regroup_if_with<mp::lift<std::is_same>, F, C>>
  {
    using type = smp::regroup_with<sfinae<F>, sfinae<C>>;
  };

  template<>
  struct smp_regroup_if_select<contract<mp::lift<std::is_same>>>
  {
    template<class C, class F>
    using f = smp::regroup_with<F, C>;
  };

  template<class Cmp>
  struct smp_regroup_if_select
  {
    template<class C, class F>
    using f = smp::invoke_twice<smp::unique_if<Cmp,
      contract<detail::smp_regroup_if_impl<
        subcontract<C>,
        contract<assume_unary_or_more<F>>,
        contract<assume_binary<Cmp>>>>
    >>;
  };

  template<class C, class F, class Cmp>
  struct smp_regroup_if_impl
  {
    template<class... xs>
    using f = contract<_tee<monadic_xs<C>,
      subcontract<smp::copy_if<smp::push_front<xs, Cmp>, F>>...
    >>;
  };
}
/// \endcond
