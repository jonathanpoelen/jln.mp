// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/map/map_find.hpp>
#include <jln/mp/map/map_contains.hpp>

namespace jln::mp::smp
{
  template<class key, class C = identity>
  using map_contains = test_contract<
    mp::is_map<>,
    mp::map_find<key, mp::always<true_, assume_unary<C>>, mp::always<false_, assume_unary<C>>>
  >;

  template<class key, class C = identity>
  using map_not_contains = test_contract<
    mp::is_map<>,
    mp::map_find<key, mp::always<false_, assume_unary<C>>, mp::always<true_, assume_unary<C>>>
  >;
}
