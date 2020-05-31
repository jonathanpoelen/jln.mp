#pragma once

#include "../functional/identity.hpp"
#include "../../functional/monadic.hpp"
#include "../../functional/recurse.hpp"

namespace jln::mp::smp
{
  template<class F, class C = identity>
  using recurse = contract<mp::recurse<
    try_subcontract<F, mp::identity, mp::always<mp::stop_iteration<na>>>,
    monadic<assume_unary<C>>>>;

  template<class F, class C = identity>
  using recurse_fix = contract<mp::recurse_fix<
    try_subcontract<F>, monadic<assume_unary<C>>>>;

  template<class F, class C = identity>
  using infinite_recurse = try_contract<mp::infinite_recurse<
    try_subcontract<F>, monadic<assume_unary<C>>>>;

  template<class F, class C = identity>
  using infinite_recurse_fix = try_contract<mp::infinite_recurse_fix<
    try_subcontract<F>, monadic<assume_unary<C>>>>;
}

/// \cond
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

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, infinite_recurse<F, C>>
  {
    using type = smp::infinite_recurse<sfinae<F>, sfinae<C>>;
  };

  template<template<class> class sfinae, class F, class C>
  struct _sfinae<sfinae, infinite_recurse_fix<F, C>>
  {
    using type = smp::infinite_recurse_fix<sfinae<F>, sfinae<C>>;
  };
}
/// \endcond
