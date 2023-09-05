// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/map/is_map.hpp>
#include <jln/mp/map/map_find.hpp>
#include <jln/mp/map/map_contains.hpp>

namespace jln::mp::smp
{
  template<class Key, class TC = identity, class FC = always<void>>
  using map_find = test_contract<
    mp::is_map<>,
    mp::map_find<Key, assume_unary<TC>, subcontract<FC>>
  >;
}

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/pop_back.hpp>
#include <jln/mp/list/front.hpp>
#include <jln/mp/map/map_update.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Key, class TC, class FC>
  struct _sfinae<sfinae, map_find<Key, TC, FC>>
  {
    using type = smp::map_find<Key, sfinae<TC>, sfinae<FC>>;
  };

  // map_insert
  template<template<class> class sfinae, class Key, class T, class C>
  struct _sfinae<sfinae, if_<map_contains<Key>, C, push_back<T, C>>>
  {
    using type = test_contract<
      is_map<>,
      if_<
        map_contains<Key>,
        assume_unary_or_more<sfinae<C>>,
        push_back<T, assume_unary_or_more<sfinae<C>>>
      >
    >;
  };

  // map_update / map_erase
  template<template<class> class sfinae, class Key, class TC, class FC, class C>
  struct _sfinae<sfinae, transform<map_find<Key, TC, FC>, C>>
  {
    using type = test_contract<
      is_map<>,
      transform<
        map_find<
          Key,
          assume_unary<sfinae<TC>>,
          assume_unary<sfinae<FC>>
        >,
        subcontract<sfinae<C>>
      >
    >;
  };

  // map_update_or_insert
  template<template<class> class sfinae, class Key, class T, class TC, class FC, class C1, class C2>
  struct _sfinae<sfinae, if_<map_contains<Key>, transform<map_find<Key, TC, FC>, C1>, push_back<T, C2>>>
  {
    using type = test_contract<
      is_map<>,
      if_<
        map_contains<Key>,
        transform<
          map_find<
            Key,
            assume_unary<sfinae<TC>>,
            assume_unary<sfinae<FC>>
          >,
          subcontract<sfinae<C1>>
        >,
        push_back<T, assume_unary_or_more<sfinae<C2>>>
      >
    >;
  };
}
/// \endcond
