#pragma once

#include "../functional/when.hpp"
#include "../functional/operators.hpp"


namespace jln::mp
{
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = call<C, call<F, xs>...>;
  };

  template<class C, class FC = unsatisfactory_concept>
  using monadic_invoke = if_<
   transform<same_as<unsatisfactory_concept_error>, or_<>>,
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
