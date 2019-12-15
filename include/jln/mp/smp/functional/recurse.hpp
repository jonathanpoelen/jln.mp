#pragma once

#include "../functional/identity.hpp"
#include "../../functional/monadic.hpp"
#include "../../functional/recurse.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using recurse = valid_contract<mp::recurse<
    try_subcontract<F, mp::identity, mp::always<mp::stop_iteration<na>>>,
    monadic<subcontract<C>>>>;

  template<class F, class C = identity>
  using recurse_fix = valid_contract<mp::recurse_fix<
    try_subcontract<F>, monadic<subcontract<C>>>>;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recurse<F, C>>
  {
    using type = smp::recurse<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, recurse_fix<F, C>>
  {
    using type = smp::recurse_fix<sfinae<F>, sfinae<C>>;
  };
}
