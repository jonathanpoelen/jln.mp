#pragma once

#include "../functional/bind.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_number;
  }

  namespace eager
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }

  template<class continuation = identity>
  using is_number = cfl<eager::is_number, continuation>;
}

#include "number.hpp"

namespace jln::mp::detail
{
  template<class x>
  struct _is_number : false_ {};

  template<int_ x>
  struct _is_number<number<x>> : true_ {};
}
