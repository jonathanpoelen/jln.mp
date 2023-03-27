#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/always.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using always = contract<mp::always<x, assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class T, class C>
  struct _sfinae<sfinae, always<T, C>>
  {
    using type = smp::always<T, sfinae<C>>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<class x, class C, class params>
  struct optimizer_impl<always<x, C>, params>
  {
    using type = typename callable_selector<params>
      ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
      ::template f<C, x, lift<always>, x>;
  };
}
/// \endcond
