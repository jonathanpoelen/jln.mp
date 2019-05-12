#pragma once

namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _sfinae;

    template<class x, class = void>
    struct _unsafe_sfinae;
  }

  template<class x>
  using sfinae = typename detail::_sfinae<x>::type;

  template<class x>
  // TODO detail::_type_member_or<sfinae, x>
  using unsafe_sfinae = typename detail::_unsafe_sfinae<x>::type;

  template<class function>
  class sfinae_barrier;
}


#include <type_traits>

namespace jln::mp::detail
{
  template<class function>
  struct _sfinae<sfinae_barrier<function>>
  {
    using type = function;
  };

  template<class x, class>
  struct _unsafe_sfinae
  {
    using type = x;
  };

  template<class x>
  struct _unsafe_sfinae<x, std::void_t<sfinae<x>>>
  : _sfinae<x>
  {};
} // namespace jln::mp
