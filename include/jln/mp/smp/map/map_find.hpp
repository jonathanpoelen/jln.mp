// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/map/is_map.hpp>
#include <jln/mp/map/map_find.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct smp_map_find_tc
  {
    using type = assume_unary<C>;
  };
}
/// \endcond

namespace jln::mp::smp
{
  template<class Key, class TC = identity, class FC = always<na>>
  using map_find = test_contract<
    mp::is_map<>,
    mp::map_find<Key, typename detail::smp_map_find_tc<TC>::type, subcontract<FC>>
  >;

  template<class key, class FC>
  using map_find_or_else = map_find<key, identity, FC>;

  template<class key, class FT>
  using map_find_or = map_find<key, identity, always<FT>>;


  template<class Key, class TC = identity, class FC = always<na>>
  using map_find_value = test_contract<
    mp::is_map<>,
    mp::map_find<Key, mp::unpack<subcontract<at1<TC>>>, subcontract<FC>>
  >;

  template<class key, class FC>
  using map_find_value_or_else = map_find_value<key, identity, FC>;

  template<class key, class FT>
  using map_find_value_or = map_find_value<key, identity, always<FT>>;


  template<class Key, class TC = listify, class FC = always<na>>
  using map_find_values = test_contract<
    mp::is_map<>,
    mp::map_find<Key, mp::unpack<mp::pop_front<subcontract<TC>>>, subcontract<FC>>
  >;

  template<class key, class FC>
  using map_find_values_or_else = map_find_values<key, listify, FC>;

  template<class key, class FT>
  using map_find_values_or = map_find_values<key, listify, always<FT>>;
}


#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/map/map_contains.hpp>
#include <jln/mp/functional/if.hpp>
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


  template<class C>
  struct smp_map_find_unpack_tc
  {
    using type = subcontract<C>;
  };

  template<class C>
  struct smp_map_find_unpack_tc<pop_front<C>>
  {
    using type = pop_front<subcontract<C>>;
  };

  template<class C>
  struct smp_map_find_unpack_tc<contract<pop_front<C>>>
  {
    using type = pop_front<C>;
  };

  template<class C>
  struct smp_map_find_unpack_tc<test_contract< // smp::pop_front
    size<greater_equal_than_c<1>>,
    drop_front_c<1, C>
  >>
  {
    using type = pop_front<C>;
  };

  template<class C>
  struct smp_map_find_tc<unpack<C>>
  {
    using type = unpack<typename smp_map_find_unpack_tc<C>::type>;
  };

  template<class C>
  struct smp_map_find_tc<contract<unpack<C>>>
  {
    using type = unpack<C>;
  };

  template<class C>
  struct smp_map_find_tc<try_contract<unpack<C>>> // smp::unpack
  {
    using type = unpack<C>;
  };

  template<class C>
  struct smp_map_find_tc<try_contract<unpack<if_< // smp::unpack<smp::pop_front>
    size<greater_equal_than_c<1>>,
    pop_front<C>,
    always<na>
  >>>>
  {
    using type = unpack<pop_front<C>>;
  };
}
/// \endcond
