// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/algorithm/index.hpp>
#include <jln/mp/algorithm/split_once.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class TC, class FC>
  struct smp_split_once_select
  {
    template<class i>
    using f = typename split_once_select<i>::template f<TC, FC>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<>>
  using split_once_if = contract<invoke_twice<try_<
    index_if<Pred, identity, always<number<-1>>>,
    detail::smp_split_once_select<assume_binary_list<TC>, subcontract<FC>>,
    mp::always<violation>
  >>>;

  template<class x, class TC = listify, class FC = clear<>>
  using split_once = split_once_if<is<x>, TC, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, split_once_if<Pred, TC, FC>>
  {
    using type = smp::split_once_if<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
