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
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), JLN_MP_TRACE_F(F)::template f, xs...>()
    )::template f<>;
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
    using counter = unpack<L, mp::counter<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using counter_wrapped_with = unpack<L, mp::counter_wrapped_with<F, C>>;
  }
}

/// \cond
namespace jln::mp
{
  template<template<class...> class F, class C>
  struct counter_wrapped_with<lift<F>, C>
  {
    template<class... xs>
    using f = typename decltype(
      unique<detail::mk_counter>::f<xs...>
      ::template f<JLN_MP_TRACE_F(C), F, xs...>()
    )::template f<>;
  };
}


#if JLN_MP_GCC
# include <jln/mp/algorithm/is_unique.hpp> // indexed_inherit
#endif

#include <utility> // std::make_index_sequence

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

  template<class, class...>
  struct counter_impl;

  struct mk_counter
  {
    template<class... xs>
    using f = counter_impl<std::make_index_sequence<sizeof...(xs)>, xs...>;
  };

#if JLN_MP_GCC

  template<class T, std::size_t i>
  number<i> index_base(indexed_item<i, T>*);

  template<std::size_t N, class... ints>
  constexpr array<N> count_elems()
  {
    array<N> counter{};

    for (auto i : std::initializer_list<std::size_t>{ints::value...}) {
      ++counter.elems[i];
    }

    return counter;
  }

  template<std::size_t... ints, class... unique_xs>
  struct counter_impl<std::index_sequence<ints...>, unique_xs...>
  {
    template<class C, template<class...> class F, class... xs>
    static auto f()
    {
      constexpr indexed_inherit<std::index_sequence<ints...>, unique_xs...>* indexed = nullptr;

      constexpr auto counters = count_elems<
        sizeof...(ints),
        decltype(index_base<xs>(indexed))...
      >();

      return always<typename C::template f<
        F<unique_xs, number<counters.elems[ints]>>...
      >>();
    }
  };

#else

  template<class T, class i>
  constexpr int_ index_base(base_item<list<i, T>>*)
  {
    return i::value;
  }

  template<std::size_t N>
  constexpr array<N> count_elems(std::initializer_list<int_> l)
  {
    array<N> counter{};

    for (auto i : l) {
      ++counter.elems[i];
    }

    return counter;
  }

  template<std::size_t... ints, class... unique_xs>
  struct counter_impl<std::integer_sequence<std::size_t, ints...>, unique_xs...>
  {
    template<class C, template<class...> class F, class... xs>
    static auto f()
    {
      constexpr inherit<list<number<ints>, unique_xs>...>* indexed = nullptr;

      constexpr auto counters = count_elems<
        sizeof...(ints)
      >(std::initializer_list<int_>{index_base<xs>(indexed)...});

      return always<typename C::template f<
        F<unique_xs, number<counters.elems[ints]>>...
      >>();
    }
  };

#endif
}
/// \endcond
