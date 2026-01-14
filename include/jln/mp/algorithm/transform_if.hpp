// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/at.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/algorithm/transform.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool>
    struct transform_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Replaces the elements for which \c Pred is true with the result of \c F.
  /// \semantics
  ///   \code
  ///   transform_if<is_floating_point, listify>::f<int, double, char>
  ///   == list< int, list<double>, char >
  ///   \endcode
  /// \treturn \sequence
  template<class Pred, class F, class C = listify>
#ifdef JLN_MP_DOXYGENATING
  using transform_if = transform<if_<Pred, F, at0<>>, C>;
#else
  struct transform_if : transform<if_<Pred, F, at0<>>, C>
  {};
#endif


  namespace emp
  {
    template<class L, class Pred, class F, class C = mp::listify>
    using transform_if = typename detail::_unpack<mp::transform_if<Pred, F, C>, L>::type;
  }
}
