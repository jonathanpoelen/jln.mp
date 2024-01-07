// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/none_of.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/front.hpp>

#include <type_traits>


namespace jln::mp
{
  /// \ingroup functional

  /// Invokes \c FC whether `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic = if_<is<na>, FC, TC>;

  /// Invokes \c FC whether first value is `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic0 = if_<front<is<na>>, FC, TC>;

  /// Invokes \c FC whether any value is `na`, otherwise \c TC.
  /// \treturn \value
  template<class TC, class FC = violation>
  using monadic_xs = if_<none_of<is<na>>, TC, FC>;

  /// Monadify only if \c x is \c na.
  /// \treturn \value
  template<class x, template<class...> class M, class TC, class FC = violation>
  using monadic_if_na = typename conditional_c<JLN_MP_IS_SAME(na, x)>
    ::template f<M<TC, FC>, TC>;
}
