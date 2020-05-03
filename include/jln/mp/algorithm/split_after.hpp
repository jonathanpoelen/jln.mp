#pragma once

#include "split.hpp"

namespace jln::mp
{
  /// \ingroup group

  /// Splits a \sequence into multiple \lists at every point that satisfy a predicate.
  /// The split value is inserted at the end of the previous list.
  /// \semantics
  ///   \code
  ///   call<split_after_if<same_as<void>, _0, _1, _2, _0, _3> == list<
  ///     list<_0>,
  ///     list<_1, _2, _0>,
  ///     list<_3>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see split_if, split_before_if
  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_after, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split_after = split_after_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = unpack<L, mp::split_after_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_after = unpack<L, mp::split_after<x, C>>;
  }
}
