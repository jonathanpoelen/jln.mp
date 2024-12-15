// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/memoize.hpp> // na
#include <jln/mp/set/set_contains.hpp>
#include <jln/mp/utility/always.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class TC, class FC, bool>
    struct set_find_impl;
  }
  /// \endcond

  /// \ingroup set

  /// Finds the element \c x in the \set.
  /// Calls \c TC with element found.
  /// If no element is found, \c FC is used with the whole \set.
  /// \pre `emp::unique<xs...> == list<xs...>`
  /// \treturn \value
  template<class x, class TC = identity, class FC = always<na>>
  struct set_find
  {
    template<class... xs>
    using f = typename detail::set_find_impl<TC, FC, JLN_MP_SET_CONTAINS(x, xs...)>
      ::template f<x, xs...>;
  };

  template<class x, class FC>
  using set_find_or_else = set_find<x, identity, FC>;

  template<class x, class FT>
  using set_find_or = set_find<x, identity, always<FT>>;

  namespace emp
  {
    template<class L, class x, class TC = mp::identity, class FC = mp::always<na>>
    using set_find = typename detail::_unpack<mp::set_find<x, TC, FC>, L>::type;

    template<class L, class x, class FC>
    using set_find_or_else = typename detail::_unpack<mp::set_find<x, mp::identity, FC>, L>::type;

    template<class L, class x, class FT>
    using set_find_or = typename detail::_unpack<mp::set_find<x, mp::identity, mp::always<FT>>, L>::type;
  }
}


#include <jln/mp/list/front.hpp>
#include <jln/mp/list/pop_front.hpp>

/// \cond
namespace jln::mp
{
  template<class x, class T>
  struct set_find<x, identity, always<T>>
  {
    template<class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(JLN_MP_SET_CONTAINS(x, xs...), x, T);
  };

  // set_contains
  template<class x, class T, class U, class C>
  struct set_find<x, always<T, C>, always<U, C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_CONDITIONAL_C_T(JLN_MP_SET_CONTAINS(x, xs...), T, U)
    );
  };

  // set_contains
  template<class x, class T, class U>
  struct set_find<x, always<T>, always<U>>
  {
    template<class... xs>
    using f = JLN_MP_CONDITIONAL_C_T(JLN_MP_SET_CONTAINS(x, xs...), T, U);
  };
}

namespace jln::mp::detail
{
  template<class TC, class FC>
  struct set_find_impl<TC, FC, true> : front<TC>
  {};

  template<class TC, class FC>
  struct set_find_impl<TC, FC, false> : pop_front<FC>
  {};
}
/// \endcond
