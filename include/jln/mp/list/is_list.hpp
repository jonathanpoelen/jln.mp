#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class x>
    struct _is_list;
  }
  /// \endcond

  /// \ingroup list

  /// Checks whether \c x is a \list.
  /// \treturn \bool
  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = JLN_MP_CALL_TRACE(C, typename detail::_is_list<x>::type);
  }

  /// \cond
  template<>
  struct is_list<identity>
  {
    template<class x>
    using f = typename detail::_is_list<x>::type;
  };
  /// \endcond
} // namespace jln::mp


#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class x>
  struct _is_list
  {
    using type = false_;
  };

  template<class... xs>
  struct _is_list<list<xs...>>
  {
    using type = true_;
  };
} // namespace jln::mp::detail
/// \endcond
