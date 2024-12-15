// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
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
    struct select_swap_index;
  }
  /// \endcond

  /// \ingroup list

  /// Swap elements at indices \c i and \c j of a \sequence.
  /// \pre `0 < i < sizeof...(xs)`
  /// \pre `0 < j < sizeof...(xs)`
  /// \treturn \sequence
  /// \note `swap_index<I, J>` == `swap_index<J, I>`
  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::select_swap_index<i < j, i == j>
    ::template f<i, j, C>;

  template<class I, class J, class C = listify>
  using swap_index = swap_index_c<I::value, J::value, C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = typename detail::_unpack<swap_index<I, J, C>, L>::type;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = typename detail::_unpack<swap_index_c<i, j, C>, L>::type;
  }
}


#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/at.hpp>

/// \cond
namespace jln::mp::detail
{
#if JLN_MP_GCC
# define JLN_MP_FN_LIST_TYPE list
# define JLN_MP_FN_TYPE class
# define JLN_MP_FN_VALUE(...) __VA_ARGS__
# define JLN_MP_FN_CALL(F) typename F::template f
#else
# define JLN_MP_FN_LIST_TYPE fn_list
# define JLN_MP_FN_TYPE template<class, class> class
# define JLN_MP_FN_VALUE(...) __VA_ARGS__::template f
# define JLN_MP_FN_CALL(F) F
  template<JLN_MP_FN_TYPE...> class fn_list;
#endif

  template<class, class>
  struct swap_index_build_seq;

  template<JLN_MP_FN_TYPE... F1, JLN_MP_FN_TYPE... F2>
  struct swap_index_build_seq<JLN_MP_FN_LIST_TYPE<F1...>, JLN_MP_FN_LIST_TYPE<F2...>>
  {
    template<class a, class b, class C, class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      JLN_MP_FN_CALL(F1)<
        a,
        JLN_MP_FN_CALL(F2)<b, xs>
      >...
    );
  };

  template<int i, int j>
  struct swap_index_builder
  {
    template<class, int... ns>
    struct indices : swap_index_build_seq<
      JLN_MP_FN_LIST_TYPE<JLN_MP_FN_VALUE(conditional_c<ns == i>)...>,
      JLN_MP_FN_LIST_TYPE<JLN_MP_FN_VALUE(conditional_c<ns == j>)...>
    >
    {};
  };

#undef JLN_MP_FN_LIST_INIT
#undef JLN_MP_FN_CALL
#undef JLN_MP_FN_TYPE

  template<unsigned i, unsigned j, int n>
  struct make_swap_index_builder : JLN_MP_MAKE_INTEGER_SEQUENCE_T(
    int, n,
    swap_index_builder<i,j>::template indices
  )
  {};

  template<unsigned i, unsigned j, class C>
  struct swap_index_impl
  {
    template<class... xs>
    using f = typename make_swap_index_builder<i, j, sizeof...(xs)>
      ::template f<
        JLN_MP_AT_C_T(j, xs...),
        JLN_MP_AT_C_T(i, xs...),
        C, xs...
      >;
  };

  template<bool, bool>
  struct select_swap_index
  {
    template<unsigned i, unsigned j, class C>
    using f = swap_index_impl<i, j, C>;
  };

  template<>
  struct select_swap_index<false, false>
  {
    template<unsigned i, unsigned j, class C>
    using f = swap_index_impl<j, i, C>;
  };

  template<unsigned i, class C>
  struct if_valid_index : call_trace_xs<C>
  {};

  template<unsigned i>
  struct if_valid_index<i, listify> : listify
  {};

  template<>
  struct select_swap_index<false, true>
  {
    template<unsigned i, unsigned j, class C>
    using f = if_valid_index<i, C>;
  };
}
/// \endcond
