#pragma once

#include "val.hpp"
#include "../functional/identity.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_val;
  }
  /// \endcond

  /// \ingroup value

  /// Check is a \value is a \val.
  /// \treturn \bool
  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = call<C, typename detail::_is_val<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using is_val = typename detail::_is_val<x>::type;
  }
}


#include "../number/number.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_val
  {
    using type = false_;
  };

#if __cplusplus >= 201703L
  template<auto x>
  struct _is_val<val<x>>
#else
  template<class T, T x>
  struct _is_val<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
/// \endcond
