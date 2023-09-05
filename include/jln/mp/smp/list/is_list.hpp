// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using is_list = try_contract<mp::is_list<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_list<C>>
  {
    using type = smp::is_list<sfinae<C>>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::unary, is_list);
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<class C, class params>
  struct optimizer_impl<is_list<C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<
        typename dispatch_list<params>
          ::template f<
            always<wrap_optimize_with_params<true_>>,
            always<wrap_optimize_with_function<lift<is_list>, types::boolean>>,
            always<wrap_optimize_with_params<false_>>
          >
      >
      ::template f<C>;
  };
}
/// \endcond
