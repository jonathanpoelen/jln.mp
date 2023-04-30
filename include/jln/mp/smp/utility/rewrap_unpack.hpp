#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/utility/rewrap_unpack.hpp>

namespace jln::mp::smp
{
  template<class C>
  using rewrap_unpack = try_contract<mp::rewrap_unpack<subcontract<C>>>;

  template<class C>
  using rewrap_unpack_append = try_contract<mp::rewrap_unpack_append<subcontract<C>>>;
}

#include <jln/mp/smp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rewrap_unpack<C>>
  {
    using type = smp::rewrap_unpack<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rewrap_unpack_append<C>>
  {
    using type = smp::rewrap_unpack_append<sfinae<C>>;
  };
}
/// \endcond
