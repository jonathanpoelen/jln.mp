// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include "jln/mp/functional/try.hpp"
#include "jln/mp/detail/compiler.hpp"

namespace ut
{
namespace
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-template")
  template<class F, class... xs>
  void invocable()
  {
    // Cuda: emp::is_invocable fails in slice and is_unique, but mp::is_invocable does not ???
    jln::mp::true_ x = typename jln::mp::is_invocable<F>::template f<xs...>{};
    (void)x;
  }

  template<class F, class... xs>
  void not_invocable()
  {
    // Cuda: infinite loop with emp::is_invocable ???
    jln::mp::false_ x = typename jln::mp::is_invocable<F>::template f<xs...>{};
    (void)x;
  }
  JLN_MP_DIAGNOSTIC_POP()
}
}
