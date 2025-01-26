// SPDX-FileCopyrightText: 2025 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/make_id.hpp>

#if JLN_MP_ENABLE_FRIEND_INJECTION

namespace jln::mp::smp
{
  template<class C = identity>
  using make_id = try_contract<mp::make_id<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, make_id<C>>
  {
    using type = smp::make_id<C>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, make_id);
}
/// \endcond

#endif
