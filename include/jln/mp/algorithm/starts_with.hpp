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
  /// \treturn \bool
  /// \see ends_with
  template<class Seq, class C = identity>
  struct starts_with
  {};

  namespace emp
  {
    template<class L, class Seq, class C = mp::identity>
    using starts_with = unpack<starts_with<Seq, C>, L>;
  }

  template<class... Ts, class C>
  struct starts_with<list<Ts...>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<take_front_c<sizeof...(Ts), lift<list, is<list<Ts...>>>>,
                   always<false_>>
      ::template f<xs...>
    );
  };
}

/// \cond
#include <jln/mp/algorithm/drop_while_xs.hpp>
#include <jln/mp/algorithm/take_while_xs.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  template<class T, class C>
  struct starts_with<list<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      typename conditional_c<1 <= sizeof...(xs)>
      ::template f<front<is<T>>, always<false_>>
      ::template f<xs...>
    );
  };

  template<class C>
  struct starts_with<list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, true_);
  };


  template<int_>
  struct optimized_index_if_xs_starts_with;

  template<>
  struct optimized_index_if_xs_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<if_<size<>, always<true_, C>>, always<number<0>, TC>, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = index_if<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_index_if_xs_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_index_if_xs_c<-int_(sizeof...(Ts))-1,
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  // optimize index_if_xs with starts_with
  template<class... Ts, class C, class TC, class FC>
  struct index_if_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_index_if_xs_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_drop_while_starts_with;

  template<>
  struct optimized_drop_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<if_<size<>, always<true_, C>>, clear<TC>, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = drop_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_drop_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_drop_while_xs_c<-int_(sizeof...(Ts))-1,
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  template<class... Ts, class C, class TC, class FC>
  struct drop_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_drop_while_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_take_while_starts_with;

  template<>
  struct optimized_take_while_starts_with<0>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = if_<if_<size<>, always<true_, C>>, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<1>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = take_while<is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_starts_with<2>
  {
    template<class C, class TC, class FC, class... Ts>
    using f = partial_take_while_xs_c<-int_(sizeof...(Ts))-1,
      starts_with<list<Ts...>, C>, TC, FC>;
  };

  template<class... Ts, class C, class TC, class FC>
  struct take_while_xs<starts_with<list<Ts...>, C>, TC, FC>
  : optimized_take_while_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};


  template<int_>
  struct optimized_take_while_extended_by_n_starts_with;

  template<>
  struct optimized_take_while_extended_by_n_starts_with<0>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = if_<if_<size<>, always<true_, C>>, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<1>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = take_while_extended_by_n_c<ExtendedByN, is<Ts..., C>, TC, FC>;
  };

  template<>
  struct optimized_take_while_extended_by_n_starts_with<2>
  {
    template<std::size_t ExtendedByN, class C, class TC, class FC, class... Ts>
    using f = partial_take_while_extended_by_n_xs_c<
      -int_(sizeof...(Ts))-1, ExtendedByN, starts_with<list<Ts...>, C>, TC, FC
    >;
  };

  template<std::size_t ExtendedByN, class... Ts, class C, class TC, class FC>
  struct take_while_extended_by_n_xs_c<ExtendedByN, starts_with<list<Ts...>, C>, TC, FC>
  : optimized_take_while_extended_by_n_starts_with<detail::min(sizeof...(Ts), 2)>
    ::template f<C, TC, FC, Ts...>
  {};
}
/// \endcond
