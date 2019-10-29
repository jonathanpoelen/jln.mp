#pragma once

#include "identity.hpp"
#include "../../functional/bind.hpp"

namespace jln::mp::smp
{
  template<template<class...> class F, class C = identity>
  using cfe = valid_contract<
    mp::try_invoke<mp::cfe<F, subcontract<C>>>>;

  template<template<class...> class F, class C = identity>
  using cfl = valid_contract<
    mp::try_invoke<mp::cfe<F, subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfl<F, C>>
  {
    using type = smp::cfl<F, sfinae<C>>;
  };

  template<template<class> class sfinae, template<class...> class F, class C>
  struct _sfinae<sfinae, cfe<F, C>>
  {
    using type = smp::cfe<F, sfinae<C>>;
  };
}
