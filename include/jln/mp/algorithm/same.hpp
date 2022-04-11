#pragma once

#include <jln/mp/detail/enumerate.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _same;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Checks whether all \values are identical.
  /// \treturn \bool
  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>);
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;
  }
}


#include <jln/mp/number/number.hpp>
#include <jln/mp/list/list.hpp>
#include <type_traits>

/// \cond
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
/// \endcond
