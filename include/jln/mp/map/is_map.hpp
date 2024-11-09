// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/list/front.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct is_map_impl;
  }
  /// \endcond

  /// \ingroup map

  /// Checks whether \c xs is a map.
  /// A map is a sequence of lists having at least one element (the key).
  /// The keys of the map must be unique.
  /// \treturn \bool
  template<class C = identity>
  using is_map = try_<detail::is_map_impl, C, always<false_, C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_map = unpack<L, mp::is_map<C>>;

    template<class... kvs>
    using is_map_xs = typename mp::is_map<>::template f<kvs...>;

    template<class L, class C = mp::identity>
    inline constexpr bool is_map_v = unpack<L, mp::is_map<C>>::value;

    template<class... kvs>
    inline constexpr bool is_map_xs_v = mp::is_map<>::f<kvs...>::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  struct is_map_impl
  {
    template<class... xs>
    using f = typename is_unique_if<>
      ::template f<typename _unpack<front<>, xs>::type...>;
  };
}
/// \endcond
