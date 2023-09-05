// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  /// \ingroup map

  /// Returns a list of the keys of \map.
  /// When is a valid map, the keys are unique, so the result is a \set.
  /// \treturn \sequence
  template<class C = listify>
  using map_keys = transform<unpack<front<>>, C>;

  /// Returns a list of the keys of \map transformed with \c F.
  /// When is a valid map, the keys are unique.
  /// \treturn \sequence
  template<class F = mp::identity, class C = listify>
  using map_keys_with = transform<unpack<front<F>>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using map_keys = unpack<L, mp::map_keys<C>>;

    template<class L, class F = mp::identity, class C = mp::listify>
    using map_keys_with = unpack<L, mp::map_keys_with<F, C>>;
  }
}
