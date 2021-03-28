#pragma once

#include <jln/mp/utility/is.hpp>
#include <jln/mp/number/operators.hpp>

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  using is_not = is<T, not_<C>>;
} // namespace jln::mp
