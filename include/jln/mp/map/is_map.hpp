// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/is_unique.hpp>
#include <jln/mp/algorithm/all_of.hpp>
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
  }
}

/// \cond
namespace jln::mp::detail
{
  struct is_map_impl
  {
    template<class... xs>
    using f = typename is_unique_impl<identity>
      ::template f<typename _unpack<front<>, xs>::type...>;
  };
}
/// \endcond
