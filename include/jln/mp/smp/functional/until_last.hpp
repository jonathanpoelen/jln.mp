// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/smp/functional/recursively.hpp>
#include <jln/mp/functional/until_last.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/type.hpp>

namespace jln::mp::smp
{
  template<class Searcher>
  using until_last = emp::try_<
    mp::type_<>,
    mp::lift<contract>,
    mp::always<bad_contract>,
    detail::until_last_impl<Searcher>
  >;

  template<template<class...> class Tpl, class Pred, class TC = listify, class FC = clear<TC>>
  using until_last_t = Tpl<Pred, recursively<
    pop_front<Tpl<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<class...> class Tpl,
    class OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<
    template<int_t, class...> class Tpl,
    int_t OffsetEnd, class Pred, class TC = listify, class FC = clear<TC>>
  using partial_until_last_t_c = Tpl<OffsetEnd, Pred, recursively<
    pop_front<Tpl<OffsetEnd, Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct until_last_impl<contract<F>>
  {
    using type = contract<typename until_last_impl<F>::type>;
  };
}
/// \endcond
