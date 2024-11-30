// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/partial_transform.hpp>
#include <jln/mp/algorithm/transform_first.hpp>

namespace jln::mp::smp
{
  template<class F, class C = listify>
  using transform_first = detail::_smp_partial_transform::f<C, F>;
}
