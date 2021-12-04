#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>

#include <type_traits>

namespace jln::mp
{
  /// \ingroup utility

  /// \treturn \bool
  template <class T, class C = identity>
  struct is
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<std::is_same<T, x>::value>);
  };
} // namespace jln::mp
