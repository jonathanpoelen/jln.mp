#pragma once

#include <jln/mp/algorithm/unique.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct counter_impl
    {
      template<class... xs>
      struct f;
    };
  }
  /// \endcond

  /// \ingroup algorithm

  /// Counts all distinct elements and returns a list of pairs containing
  /// the repeat count and the type.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   call<counter<>, int, int, char, double, int, double>
  ///   == list<
  ///     list<number<3>, int>,
  ///     list<number<1>, char>,
  ///     list<number<2>, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of \number and type
  template<class C = listify>
  struct counter
  {
    template<class... xs>
    using f = typename mp::unique<detail::counter_impl>
      ::template f<xs...>
      ::template g<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using counter = unpack<L, mp::counter<C>>;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<class x, class... xs>
  inline constexpr auto count_unique_v = (0 + ... + std::is_same<xs, x>::value);

  template<class... xs>
  struct counter_impl::f
  {
    template<class C, class... ys>
    using g = typename C::template f<mp::list<mp::number<count_unique_v<xs, ys...>>, xs>...>;
  };
}
/// \endcond
