#pragma once

#include "../functional/bind.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class x, class = void>
    struct _as_number;
  }

  namespace emp
  {
    template<class v>
    using as_number = typename detail::_as_number<v>::type;
  }

  template<class continuation = identity>
  using as_number = cfl<emp::as_number, continuation>;
}

#include "number.hpp"
#include "../config/debug.hpp"
#include "../error.hpp"
#include <type_traits>

namespace jln::mp::detail
{
  template<class v, class>
  struct _as_number JLN_MP_WITH_DEBUG(: error_occurred<as_number, err::not_a_number<v>>
    {});

  template<class v>
  struct _as_number<v, std::void_t<decltype(int_(v::value))>>
  : number<int_(v::value)> {};
}
