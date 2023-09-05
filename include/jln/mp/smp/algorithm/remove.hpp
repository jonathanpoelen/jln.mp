// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/list/join.hpp>
#include <jln/mp/smp/list/wrap_in_list.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/remove.hpp>


namespace jln::mp::smp
{
  template<class Pred, class C = listify>
  using remove_if = contract<mp::transform<
    subcontract<wrap_in_list_if_not<assume_unary_barrier<Pred>>>,
    mp::monadic_xs<mp::join<subcontract<C>>>>>;

  template<class x, class C = listify>
  using remove = contract<mp::remove<x, subcontract<C>>>;
}
