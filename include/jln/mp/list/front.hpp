// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \ingroup list

  /// Retrieves the first element of a sequence.
  /// \treturn \value
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(C, x);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = unpack<L, front<C>>;
  }
}

/// \cond
#include <jln/mp/list/lookup.hpp>

namespace jln::mp
{
  template<>
  struct front<identity> : detail::index<0>
  {};
}

// facilitates sfinae version for is_map_impl
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq>
  struct _unpack<front<C>, Seq<>>
  {};
}
/// \endcond
