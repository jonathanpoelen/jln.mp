#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \ingroup search

  /// Difference between the number of parameter \c xs and \c I::value.
  /// \semantics
  ///   Equivalent to
  ///   \code
  ///   size<push_front<I, sub<C>>>
  ///   \endcode
  /// \treturn \number
  template <class I, class C = identity>
  struct offset
  {
    template <class... xs>
    using f = typename C::template f<number<(I::value - int_{sizeof...(xs)})>>;
  };

  /// \cond
  template <class I>
  struct offset<I, identity>
  {
    template <class... xs>
    using f = number<(I::value - int_{sizeof...(xs)})>;
  };
  /// \endcond

  template<int_ i, class C = identity>
  using offset_c = offset<number<i>, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = unpack<L, mp::offset<I, C>>;

    template<class L, int_ i, class C = mp::identity>
    using offset_c = unpack<L, mp::offset<number<i>, C>>;
  }
}
