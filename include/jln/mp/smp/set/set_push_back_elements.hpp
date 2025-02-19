// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/set/set_push_back_elements.hpp>

namespace jln::mp::smp
{
  template<class C = listify>
  using set_push_back_elements = test_contract<
    mp::size<>,
    mp::if_<
      mp::front<
        mp::if_<
          mp::is_list<>,
          mp::unpack<mp::is_unique<>>
        >
      >,
      mp::set_push_back_elements<subcontract<C>>,
      violation
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, fold<cfe<emp::set_push_back>, C>>
  {
    using type = smp::set_push_back_elements<
      JLN_MP_CONDITIONAL_C_T(
        JLN_MP_IS_SAME(C, identity),
        smp::listify, sfinae<C>
      )
    >;
  };
}
/// \endcond
