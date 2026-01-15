// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<bool... bs>
    struct mk_split_before_indices;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted at the beginning of the following list.
  /// \semantics
  ///   \code
  ///   split_before_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_0, _1, _2>,
  ///     list<_0, _3>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see split_if, split_after_if
  template<class Pred, class F = listify, class C = listify>
  struct split_before_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_before_indices<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_before_if = split_before_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_before_with = split_before_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split_before = split_before_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_before_if_with = typename detail::_unpack<mp::split_before_if_with<Pred, F, C>, L>::type;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_before_if = typename detail::_unpack<mp::split_before_if_with<Pred, listify, C>, L>::type;

    template<class L, class x, class F = listify, class C = listify>
    using split_before_with = typename detail::_unpack<mp::split_before_if_with<is<x>, F, C>, L>::type;

    template<class L, class x, class C = listify>
    using split_before = typename detail::_unpack<mp::split_before_if_with<is<x>, listify, C>, L>::type;
  }
}


/// \cond
namespace jln::mp
{
  template<class T, class F, class C>
  struct split_before_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_before_indices<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_BOGUS_WNRVO()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_before_indices
  {
    static constexpr std::size_t result_len = (1 + ... + bs);

    static constexpr auto make()
    {
      array_int2<result_len> a{};
      int i = 0;
      int n = 0;

      bool bools[] {bs...};
      for (bool b : bools)
      {
        if (b)
          a.elems[++n][0] = i;
        ++i;
        ++a.elems[n][1];
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_before_indices<> : mk_split_indices<>
  {};
}
/// \endcond
