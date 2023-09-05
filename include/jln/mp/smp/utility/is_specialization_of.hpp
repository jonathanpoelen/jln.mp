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

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<template<class...> class Tpl>
  struct optimized_for_is_specialization_of
  {
    template<class C>
    using f = is_specialization_of<Tpl, C>;
  };

  template<template<class...> class Tpl, class C, class params>
  struct optimizer_impl<is_specialization_of<Tpl, C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<dispatch_optimizer<optimized_for_regular_optimizer>>
      ::template f<
        C,
        typename conditional_c<is_real_type_v<params>>
          ::template f<is_specialization_of<Tpl>, always<types::boolean>>
          ::template f<params>,
        typename conditional_c<is_real_type_v<params>>
          ::template f<lift<always>, optimized_for_is_specialization_of<Tpl>>
      >;
  };
}
/// \endcond
