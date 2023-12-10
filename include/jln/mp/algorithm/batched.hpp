// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/lookup.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool XsGreaterThatSize, bool XsModulosSize>
    struct batched_impl;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence by arbitrary size group.
  /// \post If `size <= 0`, then the result sequence is empty
  /// \semantics
  ///   \code
  ///   batched_c<2>::f<
  ///     void, void, int, void, void
  ///   > = list<
  ///     list<void, void>,
  ///     list<int, void>,
  ///     list<void>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  template<int_ size, class F = listify, class C = listify>
  struct batched_with_c
  {
    template<class... xs>
    using f = typename detail::batched_impl<size < sizeof...(xs), sizeof...(xs) % size == 0>
      ::template f<sizeof...(xs), size>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<int_ size, class C = listify>
  using batched_c = batched_with_c<size, listify, C>;

  template<class n, class F = listify, class C = listify>
  using batched_with = batched_with_c<n::value, F, C>;

  template<class n, class C = listify>
  using batched = batched_with_c<n::value, listify, C>;

  namespace emp
  {
    template<class L, class n, class F = mp::listify, class C = mp::listify>
    using batched_with = unpack<L, mp::batched_with_c<n::value, F, C>>;

    template<class L, int_ n, class F = mp::listify, class C = mp::listify>
    using batched_with_c = unpack<L, mp::batched_with_c<n, F, C>>;

    template<class L, class n, class C = mp::listify>
    using batched = unpack<L, mp::batched_with_c<n::value, mp::listify, C>>;

    template<class L, int_ n, class C = mp::listify>
    using batched_c = unpack<L, mp::batched_with_c<n, mp::listify, C>>;
  }

  /// \cond
  template<class F, class C>
  struct batched_with_c<0, F, C> : clear<C>
  {};
  /// \endcond
}


/// \cond
#include <jln/mp/algorithm/make_int_sequence.hpp>

namespace jln::mp::detail
{
  template<int... ns>
  struct extract_index
  {
    template<class C, class Indexed>
    using f = typename C::template f<typename JLN_MP_D_BUILD_INDEXED_V_GET(ns, Indexed)...>;
  };

  template<class... F>
  struct extract_outer
  {
    template<class C, class InnerC, class Indexed>
    using f = typename C::template f<typename F::template f<InnerC, Indexed>...>;

    template<int i>
    struct append
    {
      template<class, int... remaining_inner_index>
      using f = extract_outer<F..., extract_index<(i + remaining_inner_index)...>>;
    };
  };

  template<int outer_index, int outer_len, int... inner_index>
  using make_batched_inner_index = extract_index<(outer_index * outer_len + inner_index)...>;

  template<class, int... inner_index>
  struct batched_index
  {
    template<class, int... outer_index>
    struct make : extract_outer<
      make_batched_inner_index<outer_index, sizeof...(inner_index), inner_index...>...
    >
    {};
  };

  // size < nx, nx % size == 0
  template<>
  struct batched_impl<true, true>
  {
    template<int_ nx, int_ size>
    using f = JLN_MP_MAKE_INTEGER_SEQUENCE_T(int,
      nx / size,
      JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(int,
        size, batched_index
      )::template make
    );
  };

  // size < nx, nx % size != 0
  template<>
  struct batched_impl<true, false>
  {
    template<int_ nx, int_ size>
    using f = JLN_MP_D_MAKE_INTEGER_SEQUENCE_T(int,
      nx % size,
      batched_impl<true, true>::f<nx, size>
        ::template append<nx / size * size>
        ::template f
    );
  };

  template<bool>
  struct indexed_to_list_of_list
  {
    template<class C, class F, class Indexed>
    using f = typename C::template f<typename detail::_unpack<F, Indexed>::type>;
  };

  template<>
  struct indexed_to_list_of_list<false>
  {
    template<class C, class F, class Indexed>
    using f = typename C::template f<>;
  };

  // size >= nx
  template<>
  struct batched_impl<false, false>
  {
    template<int_ nx, int_ size>
    using f = indexed_to_list_of_list<nx != 0>;
  };

  template<>
  struct batched_impl<false, true>
    : batched_impl<false, false>
  {};
}
/// \endcond
