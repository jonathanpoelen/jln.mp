#pragma once

#include <jln/mp/algorithm/counter.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class C>
    struct counter_to_repeat;

    template<class... xs>
    struct regroup_if_impl;
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

  template<class Cmp = lift<std::is_same>, class F = listify, class C = listify>
  struct regroup_if_with
  {
    template<class... xs>
    using f = typename unique_if<Cmp, lift<detail::regroup_if_impl>>
      ::template f<xs...>
      ::template f<C, F, Cmp, xs...>;
  };

  template<class Cmp = lift<std::is_same>, class C = listify>
  using regroup_if = regroup_if_with<Cmp, listify, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using regroup = unpack<L, mp::regroup<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using regroup_with = unpack<L, mp::regroup_with<F, C>>;

    template<class L, class Cmp = lift<std::is_same>, class C = mp::listify>
    using regroup_if = unpack<L, mp::regroup_if<Cmp, C>>;

    template<class L, class Cmp = lift<std::is_same>, class F = mp::listify, class C = mp::listify>
    using regroup_if_with = unpack<L, mp::regroup_if_with<Cmp, F, C>>;
  }

  /// \cond
  template<class F, class C>
  struct regroup_if_with<lift<std::is_same>, F, C> : regroup_with<F, C>
  {};
  /// \endcond
}


#include <jln/mp/algorithm/repeat.hpp>
#include <jln/mp/algorithm/copy.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class C>
  struct counter_to_repeat
  {
    template<class x, class n>
    using f = typename repeat<n, C>::template f<x>;
  };

  template<class... xs>
  struct regroup_if_impl
  {
    template<class C, class F, class Cmp, class... ys>
    using f = JLN_MP_CALL_TRACE(C,
      typename copy_if<push_front<xs, Cmp>, F>::template f<ys...>...
    );
  };
}
/// \endcond
