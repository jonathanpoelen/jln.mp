// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/lift.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// \treturn \link list
  using listify = lift<list>;

  /// \cond
  template<>
  struct lift<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
} // namespace jln::mp
