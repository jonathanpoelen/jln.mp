#pragma once

#include "../functional/when.hpp"
#include "../number/operators.hpp"


namespace jln::mp
{
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = call<C, call<F, xs>...>;
  };

  template<class F, class C = identity>
  using all_of = mp::transform<F, mp::and_<C>>;

  template<class C, class FC = unsatisfactory_concept>
  using monadic_invoke = if_<
   transform<
     same_as<unsatisfactory_concept_error>, or_<>>,
   FC, C
  >;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = eager<L, mp::transform<C>>;
  }

  namespace smp
  {
    template<class F, class C = listify>
    using transform = when<
      mp::always<mp::true_>,
      mp::transform<
        mp::try_invoke<when_continuation<F>>,
        mp::monadic_invoke<when_continuation<C>>
      >
    >;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, transform<F, C>>
  {
    using type = smp::transform<sfinae<F>, sfinae<C>>;
  };
}
