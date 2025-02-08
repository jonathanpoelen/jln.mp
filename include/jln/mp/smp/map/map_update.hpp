// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/list/is_size_of.hpp>
#include <jln/mp/map/map_update.hpp>
#include <jln/mp/map/is_map.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct smp_map_update_or_insert;

  template<class>
  struct smp_map_element_key_update;

  template<class>
  struct smp_map_element_value_update;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Key, class F, class C = listify>
  using map_update = test_contract<
    mp::is_map<>,
    mp::map_update<Key, assume_unary<F>, subcontract<C>>
  >;

  template<class F>
  using map_element_key_update = test_contract<
    mp::is_size_of_c<1>,
    mp::if_<
      mp::is_map<>,
      detail::smp_map_element_key_update<assume_unary<F>>,
      violation
    >
  >;

  template<class F>
  using map_element_value_update = test_contract<
    mp::is_size_of_c<1>,
    mp::if_<
      mp::is_map<>,
      detail::smp_map_element_value_update<subcontract<F>>,
      violation
    >
  >;

  template<class Key, class F, class C = listify>
  using map_key_update = test_contract<
    mp::is_map<>,
    mp::map_update<Key, detail::smp_map_element_key_update<assume_unary<F>>, subcontract<C>>
  >;

  template<class Key, class F, class C = listify>
  using map_value_update = test_contract<
    mp::is_map<>,
    mp::map_update<Key, detail::smp_map_element_value_update<subcontract<F>>, subcontract<C>>
  >;

  template<class KV, class F, class C = listify>
  using map_update_or_insert = typename detail::smp_map_update_or_insert<mp::is_map<>::f<KV>>
    ::template f<KV, F, C>;

  template<class KV, class F, class C = listify>
  using map_value_update_or_insert = typename detail::smp_map_update_or_insert<mp::is_map<>::f<KV>>
    ::template f<KV, contract<detail::smp_map_element_value_update<subcontract<F>>>, C>;
}


#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/map/map_find.hpp> // some _sfinae<..., map_update>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_map_update_or_insert<true_>
  {
    template<class KV, class F, class C>
    using f = test_contract<
      is_map<>,
      map_update_or_insert<KV, assume_unary<F>, assume_unary_or_more<C>>
    >;
  };

  template<>
  struct smp_map_update_or_insert<false_>
    : always<bad_contract>
  {};

  template<class F>
  struct smp_map_element_key_update
  {
    template<class x>
    using f = typename detail::_unpack<partial_tee<F, monadic_xs<emp::wrapper<x>>>, x>::type;
  };

  template<class F>
  struct smp_map_element_value_update
  {
    template<class x>
    using f = typename detail::_unpack<tee<front<>, F, monadic_xs<emp::wrapper<x>>>, x>::type;
  };

  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, map_element_key_update<F>>
  {
    using type = smp::map_element_key_update<sfinae<F>>;
  };

  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, map_element_value_update<F>>
  {
    using type = smp::map_element_value_update<sfinae<F>>;
  };

  // map_update
  template<template<class> class sfinae, class Key, class F, class FC, class C>
  struct _sfinae<sfinae, transform<map_find<Key, map_element_key_update<F>, FC>, C>>
    : _sfinae<sfinae, transform<map_find<
      Key,
      contract<smp_map_element_key_update<assume_unary<sfinae<F>>>>, FC>,
      C
    >>
  {};

  // map_update
  template<template<class> class sfinae, class Key, class F, class FC, class C>
  struct _sfinae<sfinae, transform<map_find<Key, map_element_value_update<F>, FC>, C>>
    : _sfinae<sfinae, transform<map_find<
      Key,
      contract<smp_map_element_value_update<subcontract<sfinae<F>>>>, FC>,
      C
    >>
  {};

  // map_update_or_insert
  template<template<class> class sfinae, class Key, class KV, class F, class FC, class C1, class C2>
  struct _sfinae<sfinae, if_<
    map_contains<Key>,
    transform<map_find<Key, map_element_key_update<F>, FC>, C1>,
    push_back<KV, C2>
  >>
    : _sfinae<sfinae, if_<map_contains<Key>, transform<map_find<
      Key,
      contract<smp_map_element_key_update<assume_unary<sfinae<F>>>>, FC>,
      C1
    >, push_back<KV, C2>>>
  {};

  // map_update_or_insert
  template<template<class> class sfinae, class Key, class KV, class F, class FC, class C1, class C2>
  struct _sfinae<sfinae, if_<
    map_contains<Key>,
    transform<map_find<Key, map_element_value_update<F>, FC>, C1>,
    push_back<KV, C2>
  >>
    : _sfinae<sfinae, if_<map_contains<Key>, transform<map_find<
      Key,
      contract<smp_map_element_value_update<subcontract<sfinae<F>>>>, FC>,
      C1
    >, push_back<KV, C2>>>
  {};
}
/// \endcond
