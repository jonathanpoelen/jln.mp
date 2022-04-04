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

  /// \ingroup group

  /// Group identical type together.
  /// Elements are sorted in order of first appearance.
  /// \semantics
  ///   \code
  ///   regroup_with<listify>::f<int, int, char, double, int, double>
  ///   == list<
  ///     list<int, int, int>,
  ///     list<char>,
  ///     list<double, double>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list of type and \number
  template<class F, class C = listify>
  using regroup_with = counter_wrapped_with<detail::counter_to_repeat<F>, C>;

  template<class C = listify>
  using regroup = regroup_with<listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using regroup = unpack<L, mp::regroup<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using regroup_with = unpack<L, mp::regroup_with<F, C>>;
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
