// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/partial_transform.hpp>
#include <jln/mp/algorithm/transform_at.hpp>

namespace jln::mp::smp
{
  template<unsigned i, class F, class C = listify>
  using transform_at_c = typename detail::repeat_impl<
    1, i, mp::bind_back<mp::cfe<partial_transform>, F, C>
  >::template f<identity>::type;
}

JLN_MP_MAKE_REGULAR_SMP3_P(transform_at, (I), (F), (C, smp::listify), smp::transform_at_c<I::value, F, C>)
