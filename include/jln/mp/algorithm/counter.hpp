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
#if ! JLN_MP_OPTIMIZED_ALIAS && ! JLN_MP_ENABLE_DEBUG
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
#endif

#if JLN_MP_GCC
# include <jln/mp/algorithm/is_unique.hpp> // indexed_inherit
#else
# include <jln/mp/algorithm/make_int_sequence.hpp>
# include <initializer_list>
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

#if JLN_MP_GCC

  template<class T, int_ i>
  constexpr int_ index_base(indexed_item<i, T>*)
  {
    return i;
  }

  template<std::size_t N, int_... ints>
  constexpr array<N> count_elems()
  {
    array<N> counter{};

    (..., ++counter.elems[ints]);

    return counter;
  }

  JLN_MP_DIAGNOSTIC_PUSH()
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-but-set-variable")
  template<class, int_... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct impl
    {
      template<class C, template<class...> class F, class... xs>
      static auto f()
      {
        constexpr typename indexed_inherit<int_, ints...>::template f<unique_xs...>*
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
  constexpr int_ index_base(basic_item<list<i, T>>*)
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

  template<class, int_... ints>
  struct counter_impl
  {
    template<class... unique_xs>
    struct impl
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
  };

#endif

  struct mk_counter
  {
    template<class... xs>
    using f = typename JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), counter_impl)
      ::template impl<xs...>;
  };
}
/// \endcond
