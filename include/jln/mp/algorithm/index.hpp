#pragma once

#include "find.hpp"
#include "../list/size.hpp"
#include "../list/offset.hpp"
#include "../list/push_front.hpp"
#include "../utility/always.hpp"
#include "../utility/is.hpp"
#include "../number/operators.hpp"
#include "../functional/try.hpp"

namespace jln::mp
{
  /// \ingroup search

  template<class F, class C = identity>
#ifdef JLN_MP_DOXYGENATING
  using index_for = tee<size<>, F, sub<C>>;
#else
  struct index_for
  {
    template<class... xs>
    using f = typename C::template f<number<int_(sizeof...(xs)) - call<F, xs...>::value>>;
  };
#endif

  /// \cond
  template<class F>
  struct index_for<F, identity>
  {
    template<class... xs>
    using f = number<int_(sizeof...(xs)) - call<F, xs...>::value>;
  };
  /// \endcond

  template<class Pred, class C = identity, class NC = always<na>>
  struct index_if
  {
    template<class... xs>
    using f = typename find_if<Pred, offset_c<sizeof...(xs), C>, NC>
      ::template f<xs...>;
  };

  /// Returns the position of the first occurrence of a specified \value.
  /// Use \c NC::f<> if the value to search for never occurs.
  /// \treturn \number
  template<class T, class C = listify, class NC = always<na>>
  using index_of = index_if<is<T>, C, NC>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using index_for = unpack<L, mp::index_for<F, C>>;

    template<class L, class Pred, class C = mp::identity, class NC = mp::always<na>>
    using index_if = unpack<L, mp::index_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::identity, class NC = mp::always<na>>
    using index_of = unpack<L, mp::index_of<T, C, NC>>;
  }
}
