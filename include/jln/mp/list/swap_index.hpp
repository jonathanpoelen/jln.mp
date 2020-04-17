#pragma once

#include "../list/list.hpp"
#include "../utility/unpack.hpp"
#include "../number/number.hpp"

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

  /// Swap elements at indexes \c I and \c J.
  /// \pre 0 \< I \< sizeof...(xs)
  /// \pre 0 \< J \< sizeof...(xs)
  /// \return \list
  /// \note swap_index\<I, J\> == swap_index\<J, I\>
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


#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../list/at.hpp"
#include "../functional/call.hpp"

/// \cond
namespace jln::mp::detail
{
  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename join<C>::template f<
      call<take_c<i>, xs...>,
      list<call<at_c<j>, xs...>>,
      call<drop_c<i+1, take_c<j-i-1>>, xs...>,
      list<call<at_c<i>, xs...>>,
      call<drop_c<j+1>, xs...>
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
    using f = JLN_MP_DCALL(unsigned{int(sizeof...(xs)) - int{i}} < JLN_MP_MAX_CALL_ELEMENT, C, xs...);
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, true>
  {
    template<class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond
