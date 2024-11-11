// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/list/listify.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \ingroup number

  template<class C = listify>
  struct numbers
  {
    template<int_t... ns>
    using f = JLN_MP_DCALL_TRACE_XS(ns, C, number<ns>...);
  };

  /// \cond
  template<>
  struct numbers<listify>
  {
    template<int_t... ns>
    using f = list<number<ns>...>;
  };
  /// \endcond

  namespace emp
  {
    template<int_t... vs>
    using numbers = list<number<vs>...>;
  }
}
