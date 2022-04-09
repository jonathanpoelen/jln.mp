#pragma once

#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/same.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct adjacent_remove_impl;
  }
  /// \endcond

  /// \ingroup filter

  /// Removes each element in a \sequence which respect a predicate with privious element.
  /// \treturn \sequence
  template<class BinaryPred, class C = listify>
  struct adjacent_remove_if
  {
    template<class... xs>
    using f = typename detail::adjacent_remove_impl<rotate_c<-1>::f<xs...>>
      ::template f<C, BinaryPred, xs...>
      ;
  };

  /// Removes each element in a \sequence which is the same type as the privious element.
  /// \treturn \sequence
  template<class C = listify>
  using adjacent_remove = adjacent_remove_if<same<>, C>;

  namespace emp
  {
    template<class L, class BinaryPred, class C = mp::listify>
    using adjacent_remove_if = unpack<L, mp::adjacent_remove_if<BinaryPred, C>>;

    template<class L, class C = mp::listify>
    using adjacent_remove = unpack<L, mp::adjacent_remove<C>>;
  }
}


#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class BinaryPred, class x, class y>
  using adjacent_remove_transform = typename wrap_in_list_c<
    !JLN_MP_TRACE_F(BinaryPred)::template f<x, y>::value
  >::template f<x>;

  template<class y, class... ys>
  struct adjacent_remove_impl<list<y, ys...>>
  {
    template<class C, class BinaryPred, class x, class... xs>
    using f = typename detail::_join_select<sizeof...(ys)+1>::template f<
      JLN_MP_TRACE_F(C),
      list<x>,
#if JLN_MP_GCC
      adjacent_remove_transform<BinaryPred, xs, ys>...
#else
      typename wrap_in_list_c<!JLN_MP_TRACE_F(BinaryPred)::template f<xs, ys>::value>
        ::template f<xs>...
#endif
    >::type;
  };

  template<class x>
  struct adjacent_remove_impl<list<x>>
  {
    template<class C, class F, class y>
    using f = typename JLN_MP_TRACE_F(C)::template f<y>;
  };

  template<>
  struct adjacent_remove_impl<list<>>
  {
    template<class C, class F, class... ys>
    using f = JLN_MP_CALL_TRACE_0_ARG(C);
  };
}
/// \endcond
