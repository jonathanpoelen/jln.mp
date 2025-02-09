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
  template<class key, class F, class C = listify>
  using map_update = test_contract<
    mp::is_map<>,
    mp::map_update<key, assume_unary<F>, subcontract<C>>
  >;

  template<class F>
  using map_element_key_update = try_contract<
    detail::smp_map_element_key_update<assume_unary<F>>
  >;

  template<class F>
  using map_element_value_update = try_contract<
    detail::smp_map_element_value_update<subcontract<F>>
  >;

  template<class key, class F, class C = listify>
  using map_key_update = test_contract<
    mp::is_map<>,
    mp::map_update<key, detail::smp_map_element_key_update<assume_unary<F>>, subcontract<C>>
  >;

  template<class key, class F, class C = listify>
  using map_value_update = test_contract<
    mp::is_map<>,
    mp::map_update<key, detail::smp_map_element_value_update<subcontract<F>>, subcontract<C>>
  >;

  template<class kv, class F, class C = listify>
  using map_update_or_insert = typename detail::smp_map_update_or_insert<mp::is_map<>::f<kv>>
    ::template f<kv, F, C>;

  template<class k, class v, class F, class C = listify>
  using map_update_s_or_insert = test_contract<
    mp::is_map<>,
    mp::map_update_s_or_insert<k, v, assume_unary<F>, assume_unary_or_more<C>>
  >;

  template<class kv, class F, class C = listify>
  using map_value_update_or_insert = typename detail::smp_map_update_or_insert<mp::is_map<>::f<kv>>
    ::template f<kv, contract<detail::smp_map_element_value_update<subcontract<F>>>, C>;

  template<class k, class v, class F, class C = listify>
  using map_value_update_s_or_insert = test_contract<
    mp::is_map<>,
    mp::map_update_s_or_insert<k, v,
      detail::smp_map_element_value_update<subcontract<F>>, assume_unary_or_more<C>>
  >;
}


#include <jln/mp/smp/list/front.hpp>
#include <jln/mp/smp/map/map_find.hpp> // some _sfinae<..., map_update>
#include <jln/mp/functional/partial_tee.hpp>
#include <jln/mp/utility/wrapper.hpp>

/// \cond
namespace jln::mp::detail
{
  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary, (class F),
    (map_element_key_update<F>));
  JLN_MP_MAKE_EXPECTED_ARGUMENT(argument_category::unary, (class F),
    (map_element_value_update<F>));

  template<>
  struct smp_map_update_or_insert<true_>
  {
    template<class kv, class F, class C>
    using f = test_contract<
      is_map<>,
      map_update_or_insert<kv, assume_unary<F>, assume_unary_or_more<C>>
    >;
  };

  template<>
  struct smp_map_update_or_insert<false_>
    : always<bad_contract>
  {};


  template<class k>
  struct smp_map_element_key_update_dispatch
  {
    template<template<class...> class S, class... v>
    using f = typename try_<cfe<S>>::template f<k, v...>;
  };

  template<>
  struct smp_map_element_key_update_dispatch<na>
  {
    template<template<class...> class S, class... v>
    using f = na;
  };

  template<class, class>
  struct smp_map_element_key_update_impl
  {};

  template<class F, template<class...> class S, class k, class... v>
  struct smp_map_element_key_update_impl<F, S<k, v...>>
  {
    using type =
      typename smp_map_element_key_update_dispatch<JLN_MP_CALL_TRACE(F, k, v...)>
      ::template f<S, v...>;
  };

  template<class F>
  struct smp_map_element_key_update
  {
    template<class kv>
    using f = typename smp_map_element_key_update_impl<F, kv>::type;
  };


  template<class v>
  struct smp_map_element_value_update_dispatch
  {
    template<template<class...> class S, class k>
    using f = typename try_<cfe<S>>::template f<k, v>;
  };

  template<>
  struct smp_map_element_value_update_dispatch<na>
    : smp_map_element_key_update_dispatch<na>
  {};

  template<class, class>
  struct smp_map_element_value_update_impl
  {};

  template<class F, template<class...> class S, class k, class... v>
  struct smp_map_element_value_update_impl<F, S<k, v...>>
  {
    using type =
      typename smp_map_element_value_update_dispatch<JLN_MP_CALL_TRACE(F, k, v...)>
      ::template f<S, k>;
  };

  template<class F>
  struct smp_map_element_value_update
  {
    template<class kv>
    using f = typename smp_map_element_value_update_impl<F, kv>::type;
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
  template<template<class> class sfinae, class key, class F, class FC, class C>
  struct _sfinae<sfinae, transform<map_find<key, map_element_key_update<F>, FC>, C>>
    : _sfinae<sfinae, transform<map_find<
      key,
      contract<smp_map_element_key_update<assume_unary<sfinae<F>>>>, FC>,
      C
    >>
  {};

  // map_update
  template<template<class> class sfinae, class key, class F, class FC, class C>
  struct _sfinae<sfinae, transform<map_find<key, map_element_value_update<F>, FC>, C>>
    : _sfinae<sfinae, transform<map_find<
      key,
      contract<smp_map_element_value_update<subcontract<sfinae<F>>>>, FC>,
      C
    >>
  {};

  // map_update_or_insert
  template<template<class> class sfinae, class key, class kv, class F, class FC, class C1, class C2>
  struct _sfinae<sfinae, if_<
    map_contains<key>,
    transform<map_find<key, map_element_key_update<F>, FC>, C1>,
    push_back<kv, C2>
  >>
    : _sfinae<sfinae, if_<map_contains<key>, transform<map_find<
      key,
      contract<smp_map_element_key_update<assume_unary<sfinae<F>>>>, FC>,
      C1
    >, push_back<kv, C2>>>
  {};

  // map_update_or_insert
  template<template<class> class sfinae, class key, class kv, class F, class FC, class C1, class C2>
  struct _sfinae<sfinae, if_<
    map_contains<key>,
    transform<map_find<key, map_element_value_update<F>, FC>, C1>,
    push_back<kv, C2>
  >>
    : _sfinae<sfinae, if_<map_contains<key>, transform<map_find<
      key,
      contract<smp_map_element_value_update<subcontract<sfinae<F>>>>, FC>,
      C1
    >, push_back<kv, C2>>>
  {};
}
/// \endcond
