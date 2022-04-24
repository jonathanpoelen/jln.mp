#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x, class = void>
    struct _has_value_type;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether a \value to a type member.
  /// \treturn \bool
  template<class C = identity>
  struct has_value_type
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_has_value_type<x>::type);
  };

  namespace emp
  {
    template<class x>
    using has_value_type = typename detail::_has_value_type<x>::type;

    template<class x>
    inline constexpr bool has_value_type_v = detail::_has_value_type<x>::type::value;
  }

  /// \cond
  template<>
  struct has_value_type<identity>
  {
    template<class x>
    using f = typename detail::_has_value_type<x>::type;
  };
  /// \endcond
}

#include <type_traits>

/// \cond
namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_value_type<x, std::void_t<typename x::type>>
  {
    using type = true_;
  };
}
/// \endcond
