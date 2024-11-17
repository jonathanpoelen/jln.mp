// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/algorithm/rotate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool, bool>
    struct erase_values;

    template<class C, int_t start, int_t size, int_t n,
      int_t index = start < 0 ? n+start : start,
      class s = erase_values<index >= n, index < 0>,
      int_t index2 = s::template start<index>,
      int_t dropped = s::template dropped<index, size, n>>
    using erase_impl = rotate_c<
      index2,
      drop_front_c<
        dropped,
        rotate_c<n - index2 - dropped, C>
      >
    >;
  }
  /// \endcond

  /// \ingroup list

  /// Removes at most \c size elements from index \c start.
  /// A negative value represents an index starting from the end.
  /// \treturn \sequence
  template<int_t start, unsigned size = 1, class C = listify>
  struct erase_c
  {
    template<class... xs>
    using f = typename detail::erase_impl<C, start, size, int_t(sizeof...(xs))>
      ::template f<xs...>;
  };

  template<class start, class size = number<1>, class C = listify>
  using erase = erase_c<start::value, size::value, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = typename detail::_unpack<mp::erase<start, size, C>, L>::type;

    template<class L, int_t start, unsigned size = 1, class C = mp::listify>
    using erase_c = typename detail::_unpack<mp::erase_c<start, size, C>, L>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct erase_values<true, false>
  {
    template<int_t index>
    static constexpr int_t start = 0;

    template<int_t index, int_t size, int_t n>
    static constexpr int_t dropped = 0;
  };

  template<>
  struct erase_values<false, true>
  {
    template<int_t index>
    static constexpr int_t start = 0;

    template<int_t index, int_t size, int_t n>
    static constexpr int_t dropped = index + size <= 0 ? 0 : index + size <= n ? index + size : n;
  };

  template<>
  struct erase_values<false, false>
  {
    template<int_t index>
    static constexpr int_t start = index;

    template<int_t index, int_t size, int_t n>
    static constexpr int_t dropped = index + size <= n ? size : n - index;
  };
}
/// \endcond
