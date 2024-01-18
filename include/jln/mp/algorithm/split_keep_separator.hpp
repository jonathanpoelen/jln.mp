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
    struct mk_split_keep_separator_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is inserted in a new list.
  /// \semantics
  ///   \code
  ///   split_keep_separator_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_0>,
  ///     list<_1, _2>,
  ///     list<_0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_before_if
  template<class Pred = identity, class F = listify, class C = listify>
  struct split_keep_separator_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_keep_separator_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_keep_separator_if = split_keep_separator_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_keep_separator_with = split_keep_separator_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split_keep_separator = split_keep_separator_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_keep_separator_if_with = unpack<L, mp::split_keep_separator_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_keep_separator_if = unpack<L, mp::split_keep_separator_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_keep_separator_with = unpack<L, mp::split_keep_separator_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split_keep_separator = unpack<L, mp::split_keep_separator_if_with<is<x>, listify, C>>;
  }
}

/// \cond
namespace jln::mp
{
  template<class T, class F, class C>
  struct split_keep_separator_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_keep_separator_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_keep_separator_indexes
  {
    static constexpr std::size_t result_len = (0 + ... + bs) * 2 + 1;

    static constexpr auto make()
    {
      array_int2<result_len> a{};

      bool bools[] {bs...};
      int i = 0;
      int n = 0;

      for (bool b : bools)
      {
        if (b)
        {
          a.elems[++n][0] = i;
          ++a.elems[n][1] = 1;
          a.elems[++n][0] = i + 1;
        }
        else
          ++a.elems[n][1];
        ++i;
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_keep_separator_indexes<> : mk_split_indexes<>
  {};
}
/// \endcond
