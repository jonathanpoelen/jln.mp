// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/before.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before = JLN_MP_CONDITIONAL_P_C_T(
    (emp::is_list_v<Seq>),
    (contract<mp::before<Seq, subcontract<TC>, subcontract<FC>>>),
    (bad_contract)
  );
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, before<Seq, TC, FC>>
  {
    using type = smp::before<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
