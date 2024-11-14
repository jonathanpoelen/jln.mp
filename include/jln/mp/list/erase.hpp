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

    template<class C, int_ start, int_ size, int_ n,
      int_ index = start < 0 ? n+start : start,
      class s = erase_values<index >= n, index < 0>,
      int_ index2 = s::template start<index>,
      int_ dropped = s::template dropped<index, size, n>>
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
  template<int_ start, unsigned size = 1, class C = listify>
  struct erase_c
  {
    template<class... xs>
    using f = typename detail::erase_impl<C, start, size, int_(sizeof...(xs))>
      ::template f<xs...>;
  };

  template<class start, class size = number<1>, class C = listify>
  using erase = erase_c<start::value, size::value, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = typename detail::_unpack<mp::erase<start, size, C>, L>::type;

    template<class L, int_ start, unsigned size = 1, class C = mp::listify>
    using erase_c = typename detail::_unpack<mp::erase_c<start, size, C>, L>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<>
  struct erase_values<true, false>
  {
    template<int_ index>
    static constexpr int_ start = 0;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = 0;
  };

  template<>
  struct erase_values<false, true>
  {
    template<int_ index>
    static constexpr int_ start = 0;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = index + size <= 0 ? 0 : index + size <= n ? index + size : n;
  };

  template<>
  struct erase_values<false, false>
  {
    template<int_ index>
    static constexpr int_ start = index;

    template<int_ index, int_ size, int_ n>
    static constexpr int_ dropped = index + size <= n ? size : n - index;
  };
}
/// \endcond
