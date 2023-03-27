#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct same_impl;
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
      typename detail::same_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<xs...>
    );
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;
  }
}


#include <jln/mp/utility/always.hpp>
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
    using f = typename detail::same_impl<sizeof...(xs) < 3 ? sizeof...(xs) : 3>
      ::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<>
  struct same_impl<0> : always<true_>
  {};

  template<>
  struct same_impl<1> : always<true_>
  {};

  template<>
  struct same_impl<2>
  {
    template<class x, class y>
    using f = number<std::is_same<x, y>::value>;
  };

  template<>
  struct same_impl<3>
  {
    template<class x, class... xs>
    using f = number<std::is_same<list<x, xs...>, list<xs..., x>>::value>;
  };
}
/// \endcond
