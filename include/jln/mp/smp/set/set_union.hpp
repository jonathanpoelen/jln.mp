// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/algorithm/all_of.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_union.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using set_union = test_contract<
    mp::size<>,
    mp::if_<
      mp::front<mp::try_or<mp::unpack<mp::is_unique<>>>>,
      mp::if_<
        mp::pop_front<mp::all_of<mp::is_list<>>>,
        mp::set_union<subcontract<C>>,
        violation
      >,
      violation
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, set_union<C>>
  {
    using type = smp::set_union<sfinae<C>>;
  };
}
/// \endcond
