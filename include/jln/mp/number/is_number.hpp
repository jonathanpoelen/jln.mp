#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_number;
  }
  /// \endcond

  /// \ingroup number

  /// Checks whether a \value is a \number.
  /// \treturn \bool
  template<class C = identity>
  struct is_number
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_number<x>::type);
  };

  namespace emp
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }
}


#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_number
  {
    using type = false_;
  };

  template<int_ x>
  struct _is_number<number<x>>
  {
    using type = true_;
  };
}
/// \endcond
