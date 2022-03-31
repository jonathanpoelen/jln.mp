#pragma once

#include <jln/mp/functional/partial.hpp>

namespace jln::mp
{
  /// \ingroup functional

  template<class F, class C>
  using bind1st = partial<F, C>;

  template<class F, class C>
  using bind2nd = partial<identity, F, C>;
} // namespace jln::mp
