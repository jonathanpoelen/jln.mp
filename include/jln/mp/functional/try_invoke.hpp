#pragma once

#include "bind.hpp"
#include "call.hpp"
#include "fork.hpp"
#include "identity.hpp"
#include "if.hpp"
#include "sfinaefwd.hpp"
#include "../number/number.hpp"
#include "../utility/eager.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"
#include "../utility/conditional.hpp"


namespace jln::mp
{
  struct na;
  using violation = always<na>;

  namespace detail
  {
    template<class C>
    struct _subcontract;

    template<class F, class... xs>
    typename F::template f<xs...>
    _try_invoke(F*, xs*...);

    na _try_invoke(...);
  }

  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class Pred, class C>
  struct contract
  {
    template<class... xs>
    using f = typename if_<
      same_as<na>,
      cfl<violation::template f>,
      identity
    >::template f<
      typename conditional<call<Pred, xs...>>
      ::template f<C, violation>
      ::template f<xs...>
    >;
  };

  template<class C>
  struct contract<always<true_>, C>
  {
    template<class... xs>
    using f = typename if_<
      same_as<na>,
      cfl<violation::template f>,
      identity
    >::template f<call<C, xs...>>;
  };

  template<class C>
  using valid_contract = contract<always<true_>, C>;


  template<class F, class TC = identity, class FC = violation>
  struct try_invoke;

  template<class Pred, class C, class TC, class FC>
  struct try_invoke<contract<Pred, C>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional<call<Pred, xs...>>
      ::template f<fork<C, TC>, FC>
      ::template f<xs...>;
  };

  template<class Pred, class C>
  struct try_invoke<contract<Pred, C>, identity, violation>
  {
    template<class... xs>
    using f = typename conditional<call<Pred, xs...>>
      ::template f<C, violation>
      ::template f<xs...>;
  };

  template<class F, class TC, class FC>
  struct try_invoke
  {
    template<class... xs>
    using f = typename if_<same_as<na>, FC, TC>
      ::template f<decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>;
  };

  template<class F>
  struct try_invoke<F, identity, violation>
  {
    template<class... xs>
    using f = decltype(detail::_try_invoke(
      static_cast<F*>(nullptr),
      static_cast<xs*>(nullptr)...
    ));
  };

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<always<true_>, try_invoke<F, TC, FC>>;

  namespace emp
  {
    template<class L, class F, class TC = mp::identity, class FC = mp::violation>
    using try_invoke = eager<L, try_invoke<F, TC, FC>>;
  }
}

namespace jln::mp::detail
{
  // for reduce recursivity
  // TODO subcontract_for_unary
  // TODO subcontract_for_binary
  // TODO subcontract_for_list

  template<class F>
  struct _subcontract
  {
    using type = try_invoke<F>;
  };

  // template<class Pred, class C>
  // struct _subcontract<contract<Pred, C>>
  // {
  //   using type = try_invoke<contract<Pred, C>>;
  // };

  template<class C>
  struct _subcontract<contract<always<true_>, C>>
  {
    using type = C;
  };

  template<class F, class TC, class FC>
  struct _subcontract<try_invoke<F, TC, FC>>
  {
    using type = try_invoke<F, TC, FC>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, contract<Pred, C>>
  {
    using type = contract<Pred, C>;
  };

  template<template<class> class sfinae, class F, class TC, class FC>
  struct _sfinae<sfinae, try_invoke<F, TC, FC>>
  {
    using type = valid_contract<try_invoke<F, TC, FC>>;
  };
}
