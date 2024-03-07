// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/algorithm/remove_suffix.hpp>
#include <jln/mp/list/is_list.hpp>

namespace jln::mp::smp
{
  template<class Seq, class TC = listify, class FC = TC>
  using remove_suffix = typename mp::conditional_c<emp::is_list_v<Seq>>
    ::template f<contract<mp::remove_suffix<Seq, subcontract<TC>, subcontract<FC>>>, bad_contract>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Seq, class TC, class FC>
  struct _sfinae<sfinae, remove_suffix<Seq, TC, FC>>
  {
    using type = smp::remove_suffix<Seq, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
