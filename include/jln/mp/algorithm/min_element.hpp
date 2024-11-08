// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/functional/select.hpp>
#include <jln/mp/number/operators.hpp>


namespace jln::mp
{
  /// \ingroup search

  /// Returns the smallest element.
  /// If several elements in the sequence are equivalent to the smallest element,
  /// returns the element to the first such element.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \value
  /// \see last_min_element, max_element, max_last_element
  template<class Cmp = less<>, class C = identity>
#ifdef JLN_MP_DOXYGENATING
  struct min_element_with
  {
    template<class... xs>
    using f;
  };
#else
  using min_element_with = fold<reverse_select_flip<Cmp>, C>;
#endif

  template<class C = identity>
  using min_element = min_element_with<less<>, C>;


  /// Returns the smallest element.
  /// If several elements in the sequence are equivalent to the smallest element,
  /// returns the element to the last such element.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \value
  /// \see min_element, max_element, max_last_element
  template<class Cmp = less<>, class C = identity>
#ifdef JLN_MP_DOXYGENATING
  struct last_min_element_with
  {
    template<class... xs>
    using f;
  };
#else
  using last_min_element_with = fold<select<Cmp>, C>;
#endif

  template<class C = identity>
  using last_min_element = last_min_element_with<less<>, C>;


  namespace emp
  {
    template<class L, class C = mp::identity>
    using min_element = unpack<L, mp::min_element<C>>;

    template<class L, class C = mp::identity>
    using last_min_element = unpack<L, mp::last_min_element<C>>;

    template<class L, class C = mp::identity>
    inline constexpr auto min_element_v = unpack<L, mp::min_element<C>>::value;

    template<class L, class C = mp::identity>
    inline constexpr auto last_min_element_v = unpack<L, mp::last_min_element<C>>::value;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min_element_with = unpack<L, mp::min_element_with<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using last_min_element_with = unpack<L, mp::last_min_element_with<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto min_element_with_v = unpack<L, mp::min_element_with<Cmp, C>>::value;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto last_min_element_with_v = unpack<L, mp::last_min_element_with<Cmp, C>>::value;
  }
}
