#pragma once

#include "list.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_list;
  }

  // TODO is_instance_of<list>
  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = typename C::template f<typename detail::_is_list<x>::type>;
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = typename C::template f<typename detail::_is_list<x>::type>;
  }
} // namespace jln::mp

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
