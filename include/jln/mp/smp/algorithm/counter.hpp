#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/algorithm/circulant_matrix.hpp>
#include <jln/mp/algorithm/counter.hpp>
#include <jln/mp/functional/monadic.hpp>


namespace jln::mp::smp
{
  template<class C = listify>
  using counter = contract<mp::counter<assume_lists<C>>>;

  template<class F = listify, class C = listify>
  using counter_wrapped_with = contract<mp::counter_wrapped_with<
    assume_binary<F>, detail::smp_listify_or_monadic_xs<F, C>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, counter<C>>
  {
    using type = smp::counter<sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, counter_wrapped_with<F, C>>
  {
    using type = smp::counter_wrapped_with<sfinae<F>, sfinae<C>>;
  };
}
