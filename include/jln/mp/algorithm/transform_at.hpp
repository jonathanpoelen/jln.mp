// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/partial_transform.hpp>
#include <jln/mp/functional/bind_back.hpp>
#include <jln/mp/algorithm/repeat.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Replace the element at position \c i of the \sequence.
  /// \treturn \list
  template<unsigned i, class F, class C = listify>
#ifdef JLN_MP_DOXYGENATING
  struct transform_at_c
  {
    template<class... xs>
    using f;
  };
#else
  using transform_at_c = typename detail::repeat_impl<
    1, i, bind_back<cfe<partial_transform>, F, C>
  >::template f<identity>::type;
#endif

  template<class I, class F, class C = listify>
  using transform_at = transform_at_c<I::value, F, C>;

  namespace emp
  {
    template<class L, unsigned i, class F, class C = listify>
    using transform_at_c = typename detail::_unpack<mp::transform_at_c<i, F, C>, L>::type;

    template<class L, class I, class F, class C = listify>
    using transform_at = typename detail::_unpack<mp::transform_at_c<I::value, F, C>, L>::type;
  }
}
