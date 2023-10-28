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
/// \endcond
