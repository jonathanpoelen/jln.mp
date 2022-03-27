#pragma once

#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct index_if_impl;
  }
  /// \endcond

  /// \ingroup search

  /// Finds the index of the first element of \sequence
  /// that satisfies the \predicate \c Pred.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class Pred, class TC = identity, class FC = size<>>
  struct index_if
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Finds the index of the first element of \sequence that is a type \c T.
  /// Calls \c TC with the index found or \c FC with the whole \sequence.
  /// \treturn \number
  template<class T, class TC = identity, class FC = size<>>
  using index_of = index_if<is<T>, TC, FC>;

  namespace emp
  {
    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using index_if = unpack<L, mp::index_if<Pred, TC, FC>>;

    template<class L, class T, class TC = mp::identity, class FC = mp::size<>>
    using index_of = unpack<L, mp::index_of<T, TC, FC>>;
  }
}

#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct index_if_impl<_drop_while_continue>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(FC, xs...);
  };

  template<std::size_t n>
  struct index_if_impl<_drop_while_result<n>>
  {
    template<class TC, class FC, class... xs>
    using f = JLN_MP_CALL_TRACE(TC, number<sizeof...(xs)-n-1>);
  };
}
/// \endcond
