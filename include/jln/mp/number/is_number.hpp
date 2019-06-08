#pragma once

#include "../functional/when.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class... x>
    struct _is_number;
  }

  namespace eager
  {
    // TODO DOXY template<class x>
    template<class... x>
    using is_number = typename detail::_is_number<x...>::type;
  }

  template<class continuation = identity>
  using is_number = cfl<eager::is_number, continuation>;

  namespace smp
  {
    template<class continuation = identity>
    using is_number = cfl<eager::is_number, continuation>;
  }
}

#include "number.hpp"

namespace jln::mp::detail
{
  template<class... x>
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
