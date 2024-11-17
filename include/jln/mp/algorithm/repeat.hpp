// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int n>
    struct repeat_impl;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a \sequence that contains a \number of copies of the same \sequence.
  /// \pre `N >= 0`
  /// \treturn \sequence
  template<unsigned N, class C = listify>
  struct repeat_c
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE_T(
      int, N,
      detail::repeat_impl<sizeof...(xs) < 2 ? sizeof...(xs) : 2>::template impl
    )::template f<C, xs...>;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = typename detail::_unpack<mp::repeat<n, C>, L>::type;

    template<class L, int_t n, class C = mp::listify>
    using repeat_c = typename detail::_unpack<mp::repeat_c<n, C>, L>::type;
  }
}


#include <jln/mp/list/join.hpp>
#include <jln/mp/list/lookup.hpp> // index0

/// \cond
namespace jln::mp::detail
{
  template<>
  struct repeat_impl<0>
  {
    template<class, int...>
    struct impl : call_trace_c0_arg
    {};
  };

#if JLN_MP_CUDA && JLN_MP_HOST_COMPILER_GCC
  template<class x, class> using emp_index0 = x;
#  define JLN_MP_INDEX0 emp_index0
#else
#  define JLN_MP_INDEX0 index0::f
#endif

  template<>
  struct repeat_impl<1>
  {
#if JLN_MP_MSVC
    template<class C, class x, class... xs>
    using g = typename C::template f<index0::f<x, xs>...>;
#endif

    template<class, int... ns>
    struct impl
    {
#if JLN_MP_MSVC
      template<class C, class x>
      using f = g<C, x, decltype(ns)...>;
#else
      template<class C, class x>
      using f = JLN_MP_CALL_TRACE(C, JLN_MP_INDEX0<x, decltype(ns)>...);
#endif
    };
  };

  template<>
  struct repeat_impl<2>
  {
    template<class C, class L, class... xs>
    using g = typename join<C>::template f<JLN_MP_INDEX0<L, xs>...>;

    template<class, int... ns>
    struct impl
    {
      template<class C, class... xs>
      using f = g<C, list<xs...>, decltype(ns)...>;
    };
  };

#undef JLN_MP_INDEX0
}

namespace jln::mp
{
  template<class C>
  struct repeat_c<0, C>
    : detail::call_trace_xs_0<C>
  {};

  template<class C>
  struct repeat_c<1, C>
    : detail::call_trace_xs<C>
  {};
}
/// \endcond
