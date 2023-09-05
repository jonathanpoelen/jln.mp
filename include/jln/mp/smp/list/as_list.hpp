// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/as_list.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using as_list = try_contract<mp::as_list<assume_unary<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, as_list<C>>
  {
    using type = smp::as_list<sfinae<C>>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<class C, class params>
  struct optimizer_impl<as_list<C>, params>
  {
    using type = typename count_param_always_maybe_never_selector<params, 1>
      ::template f<
        typename dispatch_list<params>
          ::template f<
            always<wrap_optimize_with_params<params>>,
            always<wrap_optimize_with_function<lift<as_list>, types::any_list>>,
            always<wrap_optimize_with_function<lift<as_list>, types::any_list>>
          >
      >
      ::template f<C>;
  };
}
/// \endcond
