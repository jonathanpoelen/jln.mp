// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp::smp
{
  template<class C>
  using unpack = try_contract<mp::unpack<subcontract<C>>>;

  template<class C>
  using unpack_append = try_contract<mp::unpack_append<subcontract<C>>>;
}

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/front.hpp>

/// \cond
namespace jln::mp::detail
{
  // _unpack<front<C>> is already sfinae compliant, so unpack<try_<front<>>> -> unpack<front<>>
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<front<C>>>
  {
    using type = smp::unpack<contract<front<assume_unary<sfinae<C>>>>>;
  };


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
/// \endcond
