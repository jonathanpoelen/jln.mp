#pragma once

#include <jln/mp/set/set_contains.hpp> // inherit, basic_item
#include <jln/mp/utility/always.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class key>
    struct map_find_select;

    template<class key, class... kvs>
    using map_find_impl = decltype(detail::map_find_select<key>::f(
      static_cast<detail::inherit<kvs...>*>(nullptr)
    ));
  }
  /// \endcond

  /// \ingroup map

  /// Finds the element of the \map with a key \c key.
  /// Calls \c TC with element found.
  /// If no element is found, \c FC is used with the whole \map.
  /// \pre \c is_map<>::f<kvs...>
  /// \treturn \sequence
  template<class key, class TC = identity, class FC = always<void>>
  struct map_find
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
      ::template f<TC, FC, kvs...>;
  };

  namespace emp
  {
    template<class L, class key, class TC = mp::identity, class FC = mp::always<void>>
    using map_find = unpack<L, mp::map_find<key, TC, FC>>;
  }
}

/// \cond
namespace jln::mp
{
  template<class key, class T>
  struct map_find<key, identity, always<T>>
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
      ::template f<identity, always<T>>;
  };

  // map_contains
  template<class key, class T, class U, class C>
  struct map_find<key, always<T, C>, always<U, C>>
  {
    template<class... kvs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::map_find_impl<key, kvs...>
      ::template f<always<T>, always<U>>
    );
  };

  // map_contains
  template<class key, class T, class U>
  struct map_find<key, always<T>, always<U>>
  {
    template<class... kvs>
    using f = typename detail::map_find_impl<key, kvs...>
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
    static map_find_elem<Tpl<key, xs...>> f(basic_item<Tpl<key, xs...>>*);

    static map_find_elem<void> f(...);
  };
}
/// \endcond
