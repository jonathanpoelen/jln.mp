#pragma once

#include <jln/mp/functional/lift.hpp>
#include <jln/mp/algorithm/unique.hpp>
#include <jln/mp/algorithm/is_unique.hpp> // indexed_inherit

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class>
    struct counter_impl;

    template<class... xs>
    using mk_indexed = indexed_inherit<std::make_index_sequence<sizeof...(xs)>, xs...>;
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
      detail::counter_impl<unique<lift<detail::mk_indexed>>::f<xs...>>
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
  template<class C>
  struct counter_wrapped_with<listify, C>
  {
    template<class... xs>
    using f = typename decltype(
      detail::counter_impl<unique<lift<detail::mk_indexed>>::f<xs...>>
      ::template f<JLN_MP_TRACE_F(C), list, xs...>()
    )::template f<>;
  };
}

namespace jln::mp::detail
{
  template<class T, std::size_t i>
  constexpr std::size_t index_base(indexed_item<i, T>*)
  {
    return i;
  }

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
  JLN_MP_DIAGNOSTIC_GCC_IGNORE("-Wunused-but-set-variable")
  template<class Indexed, std::size_t N, class... xs>
  constexpr array<N> count_elems()
  {
    array<N> counter{};

    Indexed* indexed = nullptr;
    for (auto i : std::initializer_list<std::size_t>{index_base<xs>(indexed)...}) {
      ++counter.elems[i];
    }

    return counter;
  }

  template<std::size_t... i, class... ys>
  struct counter_impl<detail::indexed_inherit<std::index_sequence<i...>, ys...>>
  {
    template<class C, template<class...> class F, class... xs>
    static auto f()
    {
      constexpr auto counters = count_elems<
        detail::indexed_inherit<std::index_sequence<i...>, ys...>,
        sizeof...(i), xs...
      >();

      return always<typename C::template f<
        F<ys, number<counters.elems[i]>>...
      >>();
    }
  };
  JLN_MP_DIAGNOSTIC_POP()
}
/// \endcond
