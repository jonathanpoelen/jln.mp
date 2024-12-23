// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/insert_sequence.hpp>
#include <jln/mp/list/insert.hpp>

namespace jln::mp::smp
{
  template<int_t index, class x, class C = listify>
  using insert_c = insert_sequence_c<index, list<x>, C>;
}

JLN_MP_MAKE_REGULAR_SMP3_P(insert, (Index), (x), (C, smp::listify),
  smp::insert_c<Index::value, x, C>)
