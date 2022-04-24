#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned i, unsigned j, bool = (i < j), bool = (i == j)>
    struct _select_swap_index;
  }
  /// \endcond

  /// \ingroup list

  /// Swap elements at indexes \c I and \c J of a \sequence.
  /// \pre `0 < I < sizeof...(xs)`
  /// \pre `0 < J < sizeof...(xs)`
  /// \treturn \sequence
  /// \note `swap_index<I, J>` == `swap_index<J, I>`
  template<class I, class J, class C = listify>
  using swap_index = typename detail::_select_swap_index<
    unsigned{I::value}, unsigned{J::value}>::template f<C>;

  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<
    i, j>::template f<C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = unpack<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = unpack<L, swap_index_c<i, j, C>>;
  }
}


#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/functional/call.hpp>

/// \cond
namespace jln::mp::detail
{
  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename join<C>::template f<
      typename rotate_c<i, drop_front_c<sizeof...(xs) - i>>::template f<xs...>,
      list<typename at_c<j>::template f<xs...>>,
      typename rotate_c<j, drop_front_c<sizeof...(xs) - j + i + 1>>::template f<xs...>,
      list<typename at_c<i>::template f<xs...>>,
      typename drop_front_c<j+1>::template f<xs...>
    >;
  };

  template<unsigned i, unsigned j, bool, bool>
  struct _select_swap_index
  {
    template<class C>
    using f = swap_elem<i, j, C>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, false>
  {
    template<class C>
    using f = swap_elem<j, i, C>;
  };

  template<unsigned i, class C>
  struct if_valid_index
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<unsigned i>
  struct if_valid_index<i, listify>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, true>
  {
    template<class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond
