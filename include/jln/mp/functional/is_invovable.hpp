#pragma once

#include "identity.hpp"
#include "../number/number.hpp"

#include <type_traits>


namespace jln::mp
{
  namespace detail
  {
    template<class function, class... xs, class = std::void_t<typename function::template f<xs...>>>
    true_ _is_invocable(function*, xs*...);

    false_ _is_invocable(...);
  }

  template<class function, class continuation = identity>
  struct is_invocable
  {
    template<class... xs>
    using f = typename continuation::template f<decltype(detail::_is_invocable(static_cast<function*>(nullptr), static_cast<xs*>(nullptr)...))>;
  };

  namespace eager
  {
    template</*TODO DOXY: class function, */class... xs>
    using is_invocable = decltype(detail::_is_invocable(static_cast<xs*>(nullptr)...));
  }
}
