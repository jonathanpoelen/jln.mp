#pragma once

#include <jln/mp/list/front.hpp>
#include <jln/mp/list/take_front.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks if the \sequence begins with the given prefix.
  /// \return \bool
  template<class Seq, class C = identity>
  struct starts_with;

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using starts_with = unpack<starts_with<Seq, C>, L>;
  }

  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C,
      typename conditional_c<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<take_front_c<sizeof...(Ts), lift<list, is<list<Ts...>>>>,
                   mp::always<mp::false_>>
      ::template f<xs...>
    );
  };

  /// \cond
  template<class T, class C>
  struct starts_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<front<is<T>>, mp::always<mp::false_>>
      ::template f<xs...>
    );
  };

  template<class C>
  struct starts_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_DCALL(0 <= sizeof...(xs), C, mp::true_);
  };
  /// \endcond
}
