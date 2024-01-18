// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/lookup.hpp>
#include <jln/mp/detail/expr_to_bool.hpp>
#include <jln/mp/functional/identity.hpp>


namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class MkIndexesInt2>
    struct array_int2_index_dispatcher;

    template<bool... bs>
    struct mk_split_indexes;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The separator value is removed.
  /// \semantics
  ///   \code
  ///   split_if<is<_0>>::f<_0, _1, _2, _0, _3>
  ///   == list<
  ///     list<>,
  ///     list<_1, _2>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence
  /// \see split_before_if, split_after_if
  template<class Pred = identity, class F = listify, class C = listify>
  struct split_if_with
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_indexes<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(Pred)::template f<xs>::value
      )...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };

  template<class Pred = identity, class C = listify>
  using split_if = split_if_with<Pred, listify, C>;

  template<class x, class F = listify, class C = listify>
  using split_with = split_if_with<is<x>, F, C>;

  template<class x, class C = listify>
  using split = split_if_with<is<x>, listify, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class F = listify, class C = listify>
    using split_if_with = unpack<L, mp::split_if_with<Pred, F, C>>;

    template<class L, class Pred = mp::identity, class C = listify>
    using split_if = unpack<L, mp::split_if_with<Pred, listify, C>>;

    template<class L, class x, class F = listify, class C = listify>
    using split_with = unpack<L, mp::split_if_with<is<x>, F, C>>;

    template<class L, class x, class C = listify>
    using split = unpack<L, mp::split_if_with<is<x>, listify, C>>;
  }
}


/// \cond
#include <jln/mp/list/sliding.hpp> // sliding_inner / sliding_outer
#include <cstddef>

namespace jln::mp
{
  template<class T, class F, class C>
  struct split_if_with<is<T>, F, C>
  {
    template<class... xs>
    using f = typename detail::array_int2_index_dispatcher<
      detail::mk_split_indexes<JLN_MP_IS_SAME(T, xs)...>
    >::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F), build_indexed_v<xs...>>;
  };
}

namespace jln::mp::detail
{
  template<std::size_t N>
  struct array_int2
  {
    // index and size
    int elems[N][2];
  };

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()
  template<bool... bs>
  struct mk_split_indexes
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
        ++i;
        if (b)
          a.elems[++n][0] = i;
        else
          ++a.elems[n][1];
      }

      return a;
    }
  };
  JLN_MP_DIAGNOSTIC_POP()

  template<>
  struct mk_split_indexes<>
  {
    static constexpr std::size_t result_len = 0;

    static constexpr int make()
    {
      return 0;
    }
  };

  template<class, class...>
  struct dispatch_group_index;

  template<int... outer_index, class... Inner>
  struct dispatch_group_index<sliding_outer<int, outer_index...>, Inner...>
  {
    template<class C, class InnerC, class Indexed>
    using f = typename C::template f<
      typename Inner::template f<InnerC, Indexed, outer_index>...
    >;
  };

#if __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L
  #define JLN_MP_INDEXES_TPL_PARAM() auto indexes_pairs
  #define JLN_MP_INDEXES_TPL_VALUE() MkIndexesInt2::make()
  #if JLN_MP_MSVC
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pair_v<indexes_pairs, i>
    template<auto a, int i>
    inline constexpr auto indexes_pair_v = a.elems[i];
  #else
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pairs.elems[i]
  #endif
#else
  template<class T>
  inline constexpr auto memoize_make_fn = T::make();
  #define JLN_MP_INDEXES_TPL_PARAM() class MkIndexesInt2
  #define JLN_MP_INDEXES_TPL_VALUE() MkIndexesInt2
  #if JLN_MP_MSVC
    #define JLN_MP_INDEXES_GET_PAIR(i) indexes_pair_v<MkIndexesInt2, i>
    template<class MkIndexesInt2, int i>
    inline constexpr auto indexes_pair_v = memoize_make_fn<MkIndexesInt2>.elems[i];
  #else
    #define JLN_MP_INDEXES_GET_PAIR(i) memoize_make_fn<MkIndexesInt2>.elems[i]
  #endif
#endif

  template<class, int... i>
  struct array_int2_index_dispatcher_impl
  {
    template<JLN_MP_INDEXES_TPL_PARAM()>
    using f = dispatch_group_index<
      sliding_outer<int, JLN_MP_INDEXES_GET_PAIR(i)[0]...>,
#if JLN_MP_MEMOIZED_ALIAS || (JLN_MP_CUDA && JLN_MP_HOST_COMPILER_GCC)
      make_sliding_inner<JLN_MP_INDEXES_GET_PAIR(i)[1]>...
#else
      JLN_MP_MAKE_INTEGER_SEQUENCE_T(int, JLN_MP_INDEXES_GET_PAIR(i)[1], sliding_inner)...
#endif
    >;
  };

  template<class MkIndexesInt2>
  struct array_int2_index_dispatcher
    : JLN_MP_MAKE_INTEGER_SEQUENCE_T(int,
        MkIndexesInt2::result_len,
        array_int2_index_dispatcher_impl
      )
      ::template f<JLN_MP_INDEXES_TPL_VALUE()>
  {};

#undef JLN_MP_INDEXES_GET_PAIR
#undef JLN_MP_INDEXES_TPL_PARAM
#undef JLN_MP_INDEXES_TPL_VALUE
}
/// \endcond
