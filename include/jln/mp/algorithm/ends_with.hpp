#pragma once

#include <jln/mp/list/take_back.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks if the \sequence ends with the given prefix.
  /// \treturn \bool
  template<class Seq, class C = identity>
  struct ends_with;

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using ends_with = unpack<ends_with<Seq, C>, L>;
  }

  template<class... Ts, class C>
  struct ends_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C,
      typename conditional_c<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<take_back_c<sizeof...(Ts), lift<list, is<list<Ts...>>>>,
                   mp::always<mp::false_>>
      ::template f<xs...>
    );
  };

  /// \cond
  template<class T, class C>
  struct ends_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<take_back_c<1, is<T>>, mp::always<mp::false_>>
      ::template f<xs...>
    );
  };

  template<class C>
  struct ends_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C, mp::true_);
  };
  /// \endcond
}
