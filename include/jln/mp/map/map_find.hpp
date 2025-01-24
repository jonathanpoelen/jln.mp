// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/memoize.hpp> // na
#include <jln/mp/utility/inherit.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/unpack.hpp>
#include "jln/mp/list/pop_front.hpp"
#include "jln/mp/list/at.hpp"


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class key>
    struct map_find_select;
  }
  /// \endcond

  /// \ingroup map

  /// Finds the element of the \map with a key \c key.
  /// Calls \c TC with element found.
  /// If no element is found, \c FC is used with the whole \map.
  /// \pre \c is_map<>::f<kvs...>
  /// \treturn \sequence
  template<class key, class TC = identity, class FC = always<na>>
  struct map_find
  {
    template<class... kvs>
    using f = typename decltype(detail::map_find_select<key>::f(
      static_cast<inherit_safely<kvs...>*>(nullptr)
    ))
      ::template f<TC, FC, kvs...>;
  };

  template<class key, class FC>
  using map_find_or_else = map_find<key, identity, FC>;

  template<class key, class FT>
  using map_find_or = map_find<key, identity, always<FT>>;


  /// Finds the first value of the \map with a key \c key.
  template<class key, class TC = identity, class FC = always<na>>
  using map_find_value = map_find<key, unpack<at1<TC>>, FC>;

  template<class key, class FC>
  using map_find_value_or_else = map_find<key, unpack<at1<>>, FC>;

  template<class key, class FT>
  using map_find_value_or = map_find<key, unpack<at1<>>, always<FT>>;


  /// Finds the values of the \map with a key \c key.
  template<class key, class TC = listify, class FC = always<na>>
  using map_find_values = map_find<key, unpack<pop_front<TC>>, FC>;

  template<class key, class FC>
  using map_find_values_or_else = map_find<key, unpack<pop_front<listify>>, FC>;

  template<class key, class FT>
  using map_find_values_or = map_find<key, unpack<pop_front<listify>>, always<FT>>;


  namespace emp
  {
    template<class L, class key, class TC = mp::identity, class FC = mp::always<na>>
    using map_find = typename detail::_unpack<mp::map_find<key, TC, FC>, L>::type;

    template<class L, class key, class FC>
    using map_find_or_else = typename detail::_unpack<mp::map_find<
      key, mp::identity, FC>, L>::type;

    template<class L, class key, class FT>
    using map_find_or = typename detail::_unpack<mp::map_find<
      key, mp::identity, mp::always<FT>>, L>::type;


    template<class L, class key, class TC = mp::identity, class FC = mp::always<na>>
    using map_find_value = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::at1<TC>>, FC>, L>::type;

    template<class L, class key, class FC>
    using map_find_value_or_else = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::at1<>>, FC>, L>::type;

    template<class L, class key, class FT>
    using map_find_value_or = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::at1<>>, mp::always<FT>>, L>::type;


    template<class L, class key, class TC = mp::listify, class FC = mp::always<na>>
    using map_find_values = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::pop_front<TC>>, FC>, L>::type;

    template<class L, class key, class FC>
    using map_find_values_or_else = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::pop_front<>>, FC>, L>::type;

    template<class L, class key, class FT>
    using map_find_values_or = typename detail::_unpack<mp::map_find<
      key, mp::unpack<mp::pop_front<>>, mp::always<FT>>, L>::type;
  }
}


#include "jln/mp/algorithm/same.hpp"
#include "jln/mp/utility/conditional.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct map_found_elem
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  struct map_not_found_elem
  {
    template<class TC, class FC, class... kvs>
    using f = JLN_MP_CALL_TRACE(FC, kvs...);
  };

  template<class key>
  struct map_find_select
  {
    template<template<class...> class Tpl, class... xs>
    static map_found_elem<Tpl<key, xs...>> f(list<Tpl<key, xs...>>*);

    static map_not_found_elem f(...);
  };


  template<class TC, class T, class FC, class E>
  struct map_elem_or_T
  {
    using type = typename FC::template f<T>;
  };

  template<class TC, class T>
  struct map_elem_or_T<TC, T, identity, map_not_found_elem>
  {
    using type = T;
  };

  template<class T, class FC, class E>
  struct map_elem_or_T<identity, T, FC, map_found_elem<E>>
  {
    using type = E;
  };

  template<class TC, class T, class FC, class E>
  struct map_elem_or_T<TC, T, FC, map_found_elem<E>>
  {
    using type = typename TC::template f<E>;
  };

  template<class TC, class T, class FC, template<class...> class Tpl, class... xs>
  struct map_elem_or_T<unpack<TC>, T, FC, map_found_elem<Tpl<xs...>>>
  {
    using type = typename TC::template f<xs...>;
  };

  template<class TC, class T, class FC, template<class...> class Tpl, class k, class... xs>
  struct map_elem_or_T<unpack<pop_front<TC>>, T, FC, map_found_elem<Tpl<k, xs...>>>
  {
    using type = typename TC::template f<xs...>;
  };

  template<class T, class FC, template<class...> class Tpl, class k, class x, class... xs>
  struct map_elem_or_T<unpack<at1<>>, T, FC, map_found_elem<Tpl<k, x, xs...>>>
  {
    using type = x;
  };

  template<class TC, class T, class FC, template<class...> class Tpl, class k, class x, class... xs>
  struct map_elem_or_T<unpack<at1<TC>>, T, FC, map_found_elem<Tpl<k, x, xs...>>>
  {
    using type = typename TC::template f<x>;
  };
}

namespace jln::mp
{
  template<class key, class TC, class T, class FC>
  struct map_find<key, TC, always<T, FC>>
  {
    template<class... kvs>
    using f = typename detail::map_elem_or_T<
      TC, T, FC,
      decltype(detail::map_find_select<key>::f(
        static_cast<inherit_safely<kvs...>*>(nullptr)
      ))
     >::type;
  };
}
/// \endcond
