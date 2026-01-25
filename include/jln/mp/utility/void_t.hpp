// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

namespace jln::mp
{
  /// \ingroup trait

  /// Utility metafunction that maps a sequence of any types to the type void.
  /// \see lazy_void_t
  template<class... xs>
  using void_t = void;
}
