// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/memoize.hpp> // na
#include <jln/mp/utility/inherit.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/unpack.hpp>


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

  namespace emp
  {
    template<class L, class key, class TC = mp::identity, class FC = mp::always<na>>
    using map_find = typename detail::_unpack<mp::map_find<key, TC, FC>, L>::type;

    template<class L, class key, class FC>
    using map_find_or_else = typename detail::_unpack<mp::map_find<key, mp::identity, FC>, L>::type;

    template<class L, class key, class FT>
    using map_find_or = typename detail::_unpack<mp::map_find<key, mp::identity, mp::always<FT>>, L>::type;
  }
}

/// \cond
namespace jln::mp
{
  template<class key, class T>
  struct map_find<key, identity, always<T>>
  {
    template<class... kvs>
    using f = typename decltype(detail::map_find_select<key>::f(
      static_cast<inherit_safely<kvs...>*>(nullptr)
    ))
      ::template f<identity, always<T>>;
  };

  // map_contains
  template<class key, class T, class U, class C>
  struct map_find<key, always<T, C>, always<U, C>>
  {
    template<class... kvs>
    using f = JLN_MP_CALL_TRACE(C,
      typename decltype(detail::map_find_select<key>::f(
        static_cast<inherit_safely<kvs...>*>(nullptr)
      ))
      ::template f<always<T>, always<U>>
    );
  };

  // map_contains
  template<class key, class T, class U>
  struct map_find<key, always<T>, always<U>>
  {
    template<class... kvs>
    using f = typename decltype(detail::map_find_select<key>::f(
      static_cast<inherit_safely<kvs...>*>(nullptr)
    ))
      ::template f<always<T>, always<U>>;
  };
}

namespace jln::mp::detail
{
  template<class x>
  struct map_find_elem
  {
    template<class TC, class FC, class...>
    using f = JLN_MP_CALL_TRACE(TC, x);
  };

  template<>
  struct map_find_elem<void>
  {
    template<class TC, class FC, class... kvs>
    using f = JLN_MP_CALL_TRACE(FC, kvs...);
  };

  template<class key>
  struct map_find_select
  {
    template<template<class...> class Tpl, class... xs>
    static map_find_elem<Tpl<key, xs...>> f(list<Tpl<key, xs...>>*);

    static map_find_elem<void> f(...);
  };
}
/// \endcond
