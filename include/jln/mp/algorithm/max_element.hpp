// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/functional/select.hpp>
#include <jln/mp/number/operators.hpp>


namespace jln::mp
{
  /// \ingroup search

  /// Returns the greatest element.
  /// If several elements in the sequence are equivalent to the greatest element,
  /// returns the element to the first such element.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \value
  /// \see last_max_element, max_element, max_last_element
  template<class Cmp = less<>, class C = identity>
#ifdef JLN_MP_DOXYGENATING
  struct max_element_with
  {
    template<class... xs>
    using f;
  };
#else
  using max_element_with = fold<reverse_select<Cmp>, C>;
#endif

  template<class C = identity>
  using max_element = max_element_with<less<>, C>;


  /// Returns the greatest element.
  /// If several elements in the sequence are equivalent to the greatest element,
  /// returns the element to the last such element.
  /// \pre `sizeof...(xs) > 0`
  /// \treturn \value
  /// \see max_element, max_element, max_last_element
  template<class Cmp = less<>, class C = identity>
#ifdef JLN_MP_DOXYGENATING
  struct last_max_element_with
  {
    template<class... xs>
    using f;
  };
#else
  using last_max_element_with = fold<select_flip<Cmp>, C>;
#endif

  template<class C = identity>
  using last_max_element = last_max_element_with<less<>, C>;


  namespace emp
  {
    template<class L, class C = mp::identity>
    using max_element = unpack<L, mp::max_element<C>>;

    template<class... xs>
    using max_element_xs = typename mp::max_element_with<>::template f<xs...>;

    template<int_t... xs>
    using max_element_c = typename mp::max_element_with<>::template f<number<xs>...>;

    template<class L, class C = mp::identity>
    inline constexpr auto max_element_v = unpack<L, mp::max_element<C>>::value;

    template<class... xs>
    inline constexpr auto max_element_xs_v = mp::max_element_with<>
      ::template f<xs...>::value;

    template<int_t... xs>
    inline constexpr auto max_element_c_v = mp::max_element_with<>
      ::template f<number<xs>...>::value;


    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max_element_with = unpack<L, mp::max_element_with<Cmp, C>>;

    template<class Cmp, class... xs>
    using max_element_with_xs = typename mp::max_element_with<Cmp>::template f<xs...>;

    template<class Cmp, int_t... xs>
    using max_element_with_c = typename mp::max_element_with<Cmp>
      ::template f<number<xs>...>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto max_element_with_v = unpack<L, mp::max_element_with<Cmp, C>>::value;

    template<class Cmp, class... xs>
    inline constexpr auto max_element_with_xs_v = mp::max_element_with<Cmp>
      ::template f<xs...>::value;

    template<class Cmp, int_t... xs>
    inline constexpr auto max_element_with_c_v = mp::max_element_with<Cmp>
      ::template f<number<xs>...>::value;


    template<class L, class C = mp::identity>
    using last_max_element = unpack<L, mp::last_max_element<C>>;

    template<class... xs>
    using last_max_element_xs = typename mp::last_max_element_with<>::template f<xs...>;

    template<int_t... xs>
    using last_max_element_c = typename mp::last_max_element_with<>::template f<number<xs>...>;

    template<class L, class C = mp::identity>
    inline constexpr auto last_max_element_v = unpack<L, mp::last_max_element<C>>::value;

    template<class... xs>
    inline constexpr auto last_max_element_xs_v = mp::last_max_element_with<>
      ::template f<xs...>::value;

    template<int_t... xs>
    inline constexpr auto last_max_element_c_v = mp::last_max_element_with<>
      ::template f<number<xs>...>::value;


    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using last_max_element_with = unpack<L, mp::last_max_element_with<Cmp, C>>;

    template<class Cmp, class... xs>
    using last_max_element_with_xs = typename mp::last_max_element_with<Cmp>::template f<xs...>;

    template<class Cmp, int_t... xs>
    using last_max_element_with_c = typename mp::last_max_element_with<Cmp>
      ::template f<number<xs>...>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    inline constexpr auto last_max_element_with_v = unpack<L, mp::last_max_element_with<Cmp, C>>::value;

    template<class Cmp, class... xs>
    inline constexpr auto last_max_element_with_xs_v = mp::last_max_element_with<Cmp>
      ::template f<xs...>::value;

    template<class Cmp, int_t... xs>
    inline constexpr auto last_max_element_with_c_v = mp::last_max_element_with<Cmp>
      ::template f<number<xs>...>::value;
  }
}
