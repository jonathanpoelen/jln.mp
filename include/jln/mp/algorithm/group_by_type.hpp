#pragma once

#include <jln/mp/algorithm/counter.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C>
    struct counter_to_repeat;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Group identical type together.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   call<group_by_type_with<listify>, int, int, char, double, int, double>
  ///   == list<
  ///     list<int, int, int>,
  ///     list<char>,
  ///     list<double, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  using group_by_type_with = counter_wrapped_with<detail::counter_to_repeat<F>, C>;

  template<class C = listify>
  using group_by_type = group_by_type_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using group_by_type = unpack<L, mp::group_by_type<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using group_by_type_with = unpack<L, mp::group_by_type_with<F, C>>;
  }
}


#include <jln/mp/algorithm/repeat.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct counter_to_repeat
  {
    template<class x, class n>
    using f = typename mp::repeat<n, C>::template f<x>;
  };
}
/// \endcond
