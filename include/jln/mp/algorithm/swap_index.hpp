#pragma once

#include "../list/list.hpp"
#include "../utility/eager.hpp"
#include "../number/number.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<unsigned i, unsigned j, bool = (i < j), bool = (i == j)>
    struct _select_swap_index;
  }

  template<class I, class J, class C = listify>
  using swap_index = typename detail::_select_swap_index<
    unsigned{I::value}, unsigned{J::value}>::template f<C>;

  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<
    i, j>::template f<C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = eager<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = eager<L, swap_index_c<i, j, C>>;
  }
}


#include "../list/join.hpp"
#include "../list/drop.hpp"
#include "../list/take.hpp"
#include "../list/at.hpp"
#include "../functional/call.hpp"

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
    using f = typename detail::dcall<
      (unsigned{int(sizeof...(xs)) - int{i}} < 1000000)
    >::template f<C, xs...>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, true>
  {
    template<class C>
    using f = if_valid_index<i, C>;
  };
}
