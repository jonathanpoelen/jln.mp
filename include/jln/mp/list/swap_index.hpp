#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool, bool>
    struct _select_swap_index;
  }
  /// \endcond

  /// \ingroup list

  /// Swap elements at indexes \c i and \c j of a \sequence.
  /// \pre `0 < i < sizeof...(xs)`
  /// \pre `0 < j < sizeof...(xs)`
  /// \treturn \sequence
  /// \note `swap_index<I, J>` == `swap_index<J, I>`
  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<i < j, i == j>
    ::template f<i, j, C>;

  template<class I, class J, class C = listify>
  using swap_index = swap_index_c<I::value, J::value, C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = unpack<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = unpack<L, swap_index_c<i, j, C>>;
  }
}


#include <jln/mp/algorithm/rotate.hpp>

/// \cond
namespace jln::mp::detail
{
  //                     |        i     j
  //                     |        <--n-->
  //                     |    aaa X bbb Y ccc
  //                     |
  // rotate i            |    X bbb Y ccc aaa
  // get X ; prepend C,i |  C i bbb Y ccc aaa
  // rotate n+1          |    Y ccc aaa C i bbb
  // get Y ; append X    |      ccc aaa C i bbb X
  // rotate -n-1         |    C i bbb X ccc aaa
  // rm C,i ; append Y   |        bbb X ccc aaa Y
  //                     |
  // rotate -i           |    aaa Y bbb X ccc

  template<class y>
  struct swap_elem_push_Y
  {
    template<class C, class i, class... xs>
    using f = typename rotate_impl<sizeof...(xs) - i::value>
      ::template f<sizeof...(xs) - i::value, C, xs..., y>;
  };

  template<class x, unsigned n>
  struct swap_elem_get_Y_push_X
  {
    template<class y, class... xs>
    using f = typename rotate_impl<sizeof...(xs) - n - 1>
      ::template f<sizeof...(xs) - n - 1, swap_elem_push_Y<y>, xs..., x>;
  };

  template<unsigned n, class i, class C>
  struct swap_elem_get_X
  {
    template<class x, class... xs>
    using f = typename rotate_impl<(sizeof...(xs) & 0) + n + 1>
      ::template f<n + 1, swap_elem_get_Y_push_X<x, n>, C, i, xs...>;
  };

  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename rotate_impl<(sizeof...(xs) & 0) + i>
      ::template f<i, swap_elem_get_X<j-i, number<i>, C>, xs...>;
  };

  template<bool, bool>
  struct _select_swap_index
  {
    template<unsigned i, unsigned j, class C>
    using f = swap_elem<i, j, C>;
  };

  template<>
  struct _select_swap_index<false, false>
  {
    template<unsigned i, unsigned j, class C>
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

  template<>
  struct _select_swap_index<false, true>
  {
    template<unsigned i, unsigned j, class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond
