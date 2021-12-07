#pragma once

#include <jln/mp/algorithm/drop_while.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct take_while_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Extracts the first elements of a \sequence that satisfy a \predicate.
  /// \treturn \sequence
  /// \see take_front, take_back, drop_while
  template<class Pred, class C = listify>
  struct take_while
  {
    template<class... xs>
    using f = typename detail::take_while_impl<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<C, xs...>;
  };
}


#include <jln/mp/list/take_front.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct take_while_impl<_drop_while_continue>
  {
    template<class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C, xs...);
  };

  template<std::size_t n>
  struct take_while_impl<_drop_while_result<n>>
  {
    template<class C, class... xs>
    using f = typename take_front_c<sizeof...(xs)-n-1, C>::template f<xs...>;
  };
}
/// \encond
