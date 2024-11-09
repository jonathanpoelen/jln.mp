// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/mismatch.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/select.hpp>
#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/mismatch_index.hpp>

namespace jln::mp::smp
{
  template<class Cmp = equal<>, class C = identity>
  using mismatch_index = mismatch<
    Cmp,
    mp::front<assume_number<C>>,
    contract<
      mp::reverse_select<
        mp::front<mp::is<number<-1>>>,
        assume_number<C>
      >
    >
  >;
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, mismatch_index<Cmp, C>>
  {
    using type = smp::mismatch_index<sfinae<Cmp>, sfinae<C>>;
  };
}
