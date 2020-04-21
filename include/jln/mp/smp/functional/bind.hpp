#pragma once

#include "identity.hpp"
#include "../functional/partial.hpp"
#include "../../functional/bind.hpp"

namespace jln::mp::smp
{
  template<class F, class... xs>
  using bind = contract<mp::bind<subcontract<F>, xs...>>;

  template<class F, class... xs>
  using reverse_bind = contract<mp::reverse_bind<subcontract<F>, xs...>>;

  template<class F, class C>
  using bind1st = partial<F, C>;

  template<class F, class C>
  using bind2nd = partial<identity, F, C>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class... xs>
  struct _sfinae<sfinae, bind<F, xs...>>
  {
    using type = smp::bind<sfinae<F>, xs...>;
  };

  template<template<class> class sfinae, class F, class... xs>
  struct _sfinae<sfinae, reverse_bind<F, xs...>>
  {
    using type = smp::reverse_bind<sfinae<F>, xs...>;
  };
}
