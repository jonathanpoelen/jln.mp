// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/algorithm/unique.hpp>
#include <jln/mp/algorithm/make_int_sequence.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, int_t... ints>
    struct counter_impl;

    struct mk_counter
    {
      template<class... xs>
      using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), counter_impl)
        ::template unique<xs...>;
    };
  }
  /// \endcond

  /// \ingroup algorithm

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     F::f<int, number<3>>,
  ///     F::f<char, number<1>>,
  ///     F::f<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  struct counter_wrapped_with
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F)::template f, xs...>()
    )::template f<>;
#else
    using f = typename unique<detail::mk_counter>::f<xs...>
      ::template counter<xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F)::template f>;
#endif
  };

  /// Counts all distinct elements and returns a list of pairs containing
  /// the type and the repeat count.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   counter<F>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, number<3>>,
  ///     list<char, number<1>>,
  ///     list<double, number<2>>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class C = listify>
  using counter = counter_wrapped_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using counter = typename detail::_unpack<mp::counter<C>, L>::type;

    template<class L, class F = mp::listify, class C = mp::listify>
    using counter_wrapped_with = typename detail::_unpack<mp::counter_wrapped_with<F, C>, L>::type;
  }
}

/// \cond
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct counter_wrapped_with<cfe<F>, C>
  {
    template<class... xs>
#if JLN_MP_GCC
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), F, xs...>()
    )::template f<>;
#else
    using f = typename unique<detail::mk_counter>::f<xs...>
      ::template counter<xs...>
      ::template f<JLN_MP_TRACE_F(C), F>;
#endif
  };
}
#endif

namespace jln::mp::detail
{
  template<std::size_t N>
  struct array
  {
    int elems[N];
  };

  template<>
  struct array<0>
    : array<1>
  {};

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_IGNORE_BOGUS_WNRVO()
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()

#if JLN_MP_GCC || (!JLN_MP_MSVC && JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS)
  template<std::size_t N, class... i>
  constexpr array<N> count_elems()
  {
    array<N> counter{};
    (..., ++counter.elems[i::value]);
    return counter;
  }

  template<class T, class I>
  I index_base(list<I, T>*);
#else
  template<std::size_t N, int_t... i>
  struct count_elems
  {
    static constexpr auto counters = []{
      array<N> counter {};
      (..., ++counter.elems[i]);
      return counter;
    }();
  };

  template<class T, class I>
  constexpr int_t index_base(list<I, T>*)
  {
    return I::value;
  }
#endif

#if JLN_MP_GCC

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-but-set-variable")
  template<class, int_t... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      struct indexed_t : list<number<ints>, unique_xs>... {};

      template<class C, template<class...> class F, class... xs>
      static auto f()
      {
        constexpr indexed_t * indexed = nullptr;

        constexpr auto counters = count_elems<
          sizeof...(ints),
          decltype(index_base<xs>(indexed))...
        >();

        return always<typename C::template f<
          F<unique_xs, number<counters.elems[ints]>>...
        >>();
      }
    };
  };
  JLN_MP_DIAGNOSTIC_POP()

#else // if ! JLN_MP_GCC

#if JLN_MP_WORKAROUND(JLN_MP_MSVC, >= 1944)
  template<template<class...> class F, class S, class unique_xs, int_t i>
  using counter_impl_dispatch = F<unique_xs, number<S::counters.elems[i]>>;
#endif

  template<class, int_t... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      struct indexed_inherit : list<number<ints>, unique_xs>... {};
      static constexpr indexed_inherit * indexed = nullptr;

#if !JLN_MP_MSVC && JLN_MP_FEATURE_NONTYPE_TEMPLATE_CLASS
      template<auto counters>
      struct impl
      {
        template<class C, template<class...> class F>
        using f = typename C::template f<F<unique_xs, number<counters.elems[ints]>>...>;
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), decltype(index_base<xs>(indexed))...>()>
      {};
#else
      template<class S>
      struct impl
      {
        template<class C, template<class...> class F>
#if JLN_MP_WORKAROUND(JLN_MP_MSVC, >= 1944)
        using f = typename C::template f<counter_impl_dispatch<F, S, unique_xs, ints>...>;
#else
        using f = typename C::template f<F<unique_xs, number<S::counters.elems[ints]>>...>;
#endif
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), index_base<xs>(indexed)...>>
      {};
#endif
    };
  };

#endif

  JLN_MP_DIAGNOSTIC_POP()
}
/// \endcond
