// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/list/is_size_of.hpp> // is_size_of<> is a size<>
#include <jln/mp/list/size.hpp>

namespace jln::mp::smp
{
  template<class C = identity>
  using size = contract<mp::size<assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, size<C>>
  {
    using type = smp::size<sfinae<C>>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<bool>
  struct optimized_for_size;

  template<>
  struct optimized_for_size<false>
  {
    template<class C, class params>
    using f = optimize<C, number<count_min_param<params>::value>>;
  };

  template<>
  struct optimized_for_size<true>
  {
    template<class C, class params>
    using f = optimized_result<
      typename optimize<C, types::number>::output_result,
      size<typename optimize<C, types::number>::function>
    >;
  };

  template<class C, class params>
  struct optimizer_impl<size<C>, params>
  {
    using type = typename optimized_for_size<is_varlen_param<params>::value>
      ::template f<C, params>;
  };
}
/// \endcond
