#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _intersperse;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Inserts a \value between each element of a \sequence.
  /// \treturn \list
  /// \see prefix, suffix
  template<class x, class C = listify>
  struct intersperse
  {
    template<class... xs>
    using f = typename detail::_intersperse<sizeof...(xs) ? 1 : 0>
      ::template f<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using intersperse = unpack<L, mp::intersperse<x, C>>;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/list/pop_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _intersperse<0>
  {
    template<class C, class x>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };

  template<>
  struct _intersperse<1>
  {
    template<class C, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(xs)>
      ::template f<pop_front<C>, list<x, xs>...>::type;
  };
}
/// \endcond
