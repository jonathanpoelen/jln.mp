// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/is_specialization_of.hpp>

namespace jln::mp::smp
{
  template<template<class...> class Tpl, class C = identity>
  using is_specialization_of = try_contract<mp::is_specialization_of<Tpl, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class Tpl, class C>
  struct _sfinae<sfinae, is_specialization_of<Tpl, C>>
  {
    using type = smp::is_specialization_of<Tpl, sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary,
    (template<class...> class Tpl, class C),
    (is_specialization_of<Tpl, C>));
}
/// \endcond
