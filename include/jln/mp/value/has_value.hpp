#pragma once

#include "../functional/identity.hpp"
#include "../number/number.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value;
  }
  /// \endcond

  /// \ingroup value

  /// Check is a \value to a value member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = typename C::template f<
      typename detail::_has_value<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v = detail::_has_value<x>::type::value;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, decltype(void(x::value))>
  {
    using type = true_;
  };
}
/// \endcond
