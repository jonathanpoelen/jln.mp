#pragma once

#include "../functional/identity.hpp"
#include "../../utility/unpack.hpp"

namespace jln::mp::smp
{
  template<class C>
  using unpack = try_contract<mp::unpack<subcontract<C>>>;

  template<class C>
  using unpack_append = try_contract<mp::unpack_append<subcontract<C>>>;
}

#include "../list/list.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<C>>
  {
    using type = smp::unpack<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack_append<C>>
  {
    using type = smp::unpack_append<sfinae<C>>;
  };

  
  template<>
  struct optimize_useless_unpack<smp::unpack<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };
}
