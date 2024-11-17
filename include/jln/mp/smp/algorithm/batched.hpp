// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/sliding.hpp>
#include <jln/mp/algorithm/batched.hpp>

namespace jln::mp::smp
{
  template<int_t size, class C = listify>
  using batched_c = typename detail::smp_sliding_with_c<mp::listify, (size > 0)>
    ::template f<size, size, C>;

  template<int_t size, class F = listify, class C = listify>
  using batched_with_c = typename detail::smp_sliding_with_c<subcontract<F>, (size > 0)>
    ::template f<size, size, C>;

  template<class size, class C = listify>
  using batched = strided_sliding_with<size, size, smp::listify, C>;

  template<class size, class F = listify, class C = listify>
  using batched_with = strided_sliding_with<size, size, F, C>;
}
