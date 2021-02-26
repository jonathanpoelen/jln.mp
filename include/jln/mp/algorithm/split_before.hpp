#pragma once

#include "split.hpp"

namespace jln::mp
{
  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The split value is inserted at the beginning of the following list.
  /// \semantics
  ///   \code
  ///   call<split_before_if<is<void>, _0, _1, _2, _0, _3> == list<
  ///     list<>,
  ///     list<_0, _1, _2>,
  ///     list<_0, _3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_after_if
  template<class Pred, class C = listify>
  struct split_before_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_before, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split_before = split_before_if<is<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_before_if = unpack<L, mp::split_before_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_before = unpack<L, mp::split_before<x, C>>;
  }
}
