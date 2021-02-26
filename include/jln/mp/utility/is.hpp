#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"

#include <type_traits>

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  struct is
  {
    template <class x>
    using f = typename C::template f<number<std::is_same<T, x>::value>>;
  };
} // namespace jln::mp
