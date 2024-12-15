// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/clear.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/before_after.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class SubC1 = listify, class SubC2 = SubC1,
           class TC = listify, class FC = clear<TC>>
  using before_after_with = JLN_MP_CONDITIONAL_P_C_T(
    (emp::is_list_v<Seq>),
    (contract<mp::before_after_with<Seq, subcontract<SubC1>, subcontract<SubC2>,
              assume_binary<TC>, subcontract<FC>>>),
    (bad_contract)
  );

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class SubC1, class SubC2, class TC, class FC>
  struct _sfinae<sfinae, before_after_with<Seq, SubC1, SubC2, TC, FC>>
  {
    using type = smp::before_after_with<Seq, sfinae<SubC1>, sfinae<SubC2>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
