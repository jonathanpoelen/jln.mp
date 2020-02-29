#pragma once

#include "../config/enumerate.hpp"
#include "../functional/identity.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _same;
  }

  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;
  }
}


#include "../number/number.hpp"
#include "../list/list.hpp"
#include <type_traits>

namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<>
  struct _same<0>
  {
    template<class...>
    using f = mp::true_;
  };

  template<>
  struct _same<1>
  {
    template<class>
    using f = mp::true_;
  };

  template<>
  struct _same<2>
  {
    template<class x, class y>
    using f = mp::number<std::is_same<x, y>::value>;
  };

  template<>
  struct _same<3>
  {
    template<class x, class... xs>
    using f = mp::number<std::is_same<list<x, xs...>, list<xs..., x>>::value>;
  };
}
