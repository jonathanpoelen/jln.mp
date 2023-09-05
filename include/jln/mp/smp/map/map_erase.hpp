// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/map/is_map.hpp>
#include <jln/mp/map/map_erase.hpp>

namespace jln::mp::smp
{
  template<class Key, class C = listify>
  using map_erase = test_contract<
    mp::is_map<>,
    mp::map_erase<Key, subcontract<C>>
  >;
}

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/alignof.hpp>
#include <jln/mp/smp/list/join.hpp>
#include <jln/mp/smp/map/map_find.hpp> // contains _sfinae<..., map_erase>

namespace jln::mp::detail
{
  template<template<class> class sfinae, class Key, class... xs, class C>
  struct _sfinae<sfinae, transform<map_find<Key, always<list<xs...>>, listify>, C>>
  {
    using type = test_contract<
      is_map<>,
      transform<
        map_find<Key, always<list<xs...>>, listify>,
        assume_lists<sfinae<C>>
      >
    >;
  };
}
