// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct mk_counter;
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
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct counter_wrapped_with<lift<F>, C>
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

#if JLN_MP_GCC
# include <jln/mp/algorithm/is_unique.hpp> // indexed_inherit
#else
# include <jln/mp/algorithm/make_int_sequence.hpp>
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
  JLN_MP_DIAGNOSTIC_IGNORE_UNSAFE_BUFFER_USAGE()

#if JLN_MP_GCC || (!JLN_MP_MSVC && __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L)
  template<std::size_t N, int_t... i>
  constexpr array<N> count_elems()
  {
    array<N> counter{};
    (..., ++counter.elems[i]);
    return counter;
  }
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
#endif

#if JLN_MP_GCC

  template<class T, int_t i>
  constexpr int_t index_base(indexed_item<i, T>*)
  {
    return i;
  }

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-but-set-variable")
  template<class, int_t... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      template<class C, template<class...> class F, class... xs>
      static auto f()
      {
        constexpr typename indexed_inherit<int_t, ints...>::template f<unique_xs...>*
          indexed = nullptr;

        constexpr auto counters = count_elems<
          sizeof...(ints),
          index_base<xs>(indexed)...
        >();

        return always<typename C::template f<
          F<unique_xs, number<counters.elems[ints]>>...
        >>();
      }
    };
  };
  JLN_MP_DIAGNOSTIC_POP()

#else

  template<class T, class i>
  constexpr int_t index_base(basic_item<list<i, T>>*)
  {
    return i::value;
  }

 template<class, int_t... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct unique
    {
      static constexpr detail::inherit<list<number<ints>, unique_xs>...>* indexed = nullptr;

#if !JLN_MP_MSVC && __cplusplus >= 202002L && __cpp_nontype_template_args >= 201911L
      template<auto counters>
      struct impl
      {
        template<class C, template<class...> class F>
        using f = typename C::template f<F<unique_xs, number<counters.elems[ints]>>...>;
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), index_base2<xs>(indexed)...>()>
      {};
#else
      template<class S>
      struct impl
      {
        template<class C, template<class...> class F>
        using f = typename C::template f<F<unique_xs, number<S::counters.elems[ints]>>...>;
      };

      template<class... xs>
      struct counter : impl<count_elems<sizeof...(ints), index_base<xs>(indexed)...>>
      {};
#endif
    };
  };

#endif

  JLN_MP_DIAGNOSTIC_POP()

  struct mk_counter
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), counter_impl)
      ::template unique<xs...>;
  };
}
/// \endcond
