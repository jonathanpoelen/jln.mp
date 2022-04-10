#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/algorithm/regroup.hpp>


namespace jln::mp::smp
{
  template<class C = listify>
  using regroup = contract<mp::regroup<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using regroup_with = contract<mp::counter_wrapped_with<
    mp::if_<
      mp::size<mp::is<mp::number<2>>>,
      detail::counter_to_repeat<subcontract<F>>,
      violation
    >,
    detail::smp_listify_or_monadic_xs<F, C>>
  >;
}

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
}
