// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/same.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }
  /// \endcond

  /// \ingroup filter

  /// Returns a list with duplicate elements removed.
  /// \treturn \set
  template<class C = listify>
  using unique = typename detail::mk_unique<same<>, C>::type;

  /// Returns a list with duplicate elements removed.
  /// Only the first element found is kept.
  /// \treturn \sequence
  template<class Cmp = same<>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = typename detail::_unpack<unique<C>, L>::type;

    template<class L, class Cmp = mp::same<>, class C = mp::listify>
    using unique_if = typename detail::_unpack<unique_if<Cmp, C>, L>::type;
  }
}


#include <jln/mp/algorithm/fold.hpp>
#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/push_back.hpp>
#include <jln/mp/set/set_push_back.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class x, class... xs>
    using f = JLN_MP_CONDITIONAL_P_C_T(
      (none_of<push_back<x, Cmp>>::template f<xs...>::value),
      (list<xs..., x>),
      (list<xs...>)
    );
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold<
      unpack<_set_cmp_push_back<JLN_MP_TRACE_F(Cmp)>>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<same<>, C>
  {
    using type = push_front<list<>, fold<
      lift<emp::set_push_back>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };
}
/// \endcond
