// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  #ifndef JLN_MP_PACK_AT
  namespace detail
  {
    template<class x, class...>
    struct front_impl
    {
      using type = x;
    };
  }
  #endif
  /// \endcond

  /// \ingroup list

  /// Retrieves the first element of a sequence.
  /// \treturn \value
  template<class C = identity>
  struct front
  {
#ifdef JLN_MP_PACK_AT
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, JLN_MP_PACK_AT(xs, 0));
    JLN_MP_DIAGNOSTIC_POP()
#else
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, typename detail::front_impl<xs...>::type);
#endif
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = typename detail::_unpack<front<C>, L>::type;
  }
}


#include <jln/mp/list/lookup.hpp>

/// \cond
namespace jln::mp
{
  template<>
  struct front<identity>
  {
#ifdef JLN_MP_PACK_AT
    JLN_MP_DIAGNOSTIC_PUSH()
    JLN_MP_DIAGNOSTIC_IGNORE_PACK_INDEXING_EXTENSION()
    template<class... xs>
    using f = JLN_MP_PACK_AT(xs, 0);
    JLN_MP_DIAGNOSTIC_POP()
#else
    template<class... xs>
    using f = typename detail::front_impl<xs...>::type;
#endif
  };
}

// facilitates sfinae version for is_map_impl
namespace jln::mp::detail
{
  template<class C, template<class...> class Seq>
  struct _unpack<front<C>, Seq<>>
  {};
}
/// \endcond
