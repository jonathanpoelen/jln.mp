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
#include "../number/operators.hpp"


namespace jln::mp
{
  struct na;
  using is_na = same_as<na>;
  using violation = always<na>;

  namespace detail
  {
    template<class C> struct _subcontract;
    template<class x> struct _optimize_try_invoke;

    template<class F> struct _assume_number { using type = F; };
    template<class F> struct _assume_positive { using type = F; };
    template<class F> struct _assume_strictly_positive { using type = F; };
    template<class F> struct _assume_list { using type = F; };
    template<class F> struct _assume_unary { using type = F; };
    template<class F> struct _assume_unary_number { using type = F; };
    template<class F> struct _assume_unary_positive { using type = F; };
    template<class F> struct _assume_unary_strictly_positive { using type = F; };
    template<class F> struct _assume_unary_list { using type = F; };
    template<class F> struct _assume_binary { using type = F; };
    template<class F> struct _assume_binary_number { using type = F; };
    template<class F> struct _assume_binary_positive { using type = F; };
    template<class F> struct _assume_binary_strictly_positive { using type = F; };
    template<class F> struct _assume_binary_list { using type = F; };
    template<class F> struct _assume_xs_number { using type = F; };
    template<class F> struct _assume_xs_positive { using type = F; };
    template<class F> struct _assume_xs_strictly_positive { using type = F; };
    template<class F> struct _assume_xs_list { using type = F; };

    template<class F, class... xs>
    typename F::template f<xs...>
    _try_invoke(F*, xs*...);

    na _try_invoke(...);
  }

  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class C>
  using assume_number = typename detail::_assume_number<subcontract<C>>::type;

  template<class C>
  using assume_unary = typename detail::_assume_unary<subcontract<C>>::type;

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

  using bad_contract = contract<always<false_>, listify>;


  template<class F, class TC = identity, class FC = violation>
  struct try_invoke;

  // TODO try_invoke_or<F, FC> = try_invoke<F, identity, FC>

  template<class Pred, class C, class TC, class FC>
  struct try_invoke<contract<Pred, C>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional<call<Pred, xs...>>
      ::template f<fork<C, if_<same_as<na>, FC, TC>>, FC>
      ::template f<xs...>;
  };

  template<class Pred, class C, class TFC>
  struct try_invoke<contract<Pred, C>, always<true_, TFC>, always<false_, TFC>>
  {
    template<class... xs>
    using f = typename conditional<call<Pred, xs...>>
      ::template f<
        fork<C, same_as<na, not_<TFC>>>,
        always<false_, TFC>>
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

  template<class F, class TFC>
  struct try_invoke<F, always<true_, TFC>, always<false_, TFC>>
  {
    template<class... xs>
    using f = call<TFC, number<!std::is_same<na,
      decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>::value>>;
  };

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<always<true_>, try_invoke<F, TC, FC>>;

  namespace emp
  {
    template<class L, class F, class TC = mp::identity, class FC = mp::violation>
    using try_invoke = eager<L, try_invoke<F, TC, FC>>;
  }

  template<class F>
  struct contract_barrier
  {
    template<class... xs>
    using f = call<F, xs...>;
  };

  template<class F>
  using subcontract_barrier = contract_barrier<subcontract<F>>;

  template<class F, class TC = identity, class FC = violation>
  using try_subcontract = typename detail::_optimize_try_invoke<
    try_invoke<subcontract<F>, TC, FC>>::type;
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

  template<class F>
  struct _subcontract<contract_barrier<F>>
  {
    using type = F;
  };


  struct argument_category
  {
    enum tag
    {
      strictly_positive = 0b000'0001,
      positive          = 0b000'0010,
      number            = 0b000'0100,
      list              = 0b000'1000,

      _positive         = positive | strictly_positive,
      _number           = number | _positive,

      unary             = 0b001'0000,
      binary            = 0b010'0000,
      variadic          = 0b100'0000,

      unary_strictly_positive = unary | strictly_positive,
      unary_positive = unary | positive,
      unary_number = unary | number,
    };
  };

  template<class F>
  struct expected_argument : number<0>
  {};

  // TODO != number -> violation ?
  template<class F>
  using _assume_number_cond = conditional_c<(
    (expected_argument<F>::value
      & (detail::argument_category::_number
        | detail::argument_category::unary)
    ) > detail::argument_category::unary
  )>;

  template<class F>
  struct _assume_number<try_invoke<F, identity, violation>>
  {
    using type = typename _assume_number_cond<F>::template f<
      F,
      try_invoke<F, identity, violation>
    >;
  };


  template<class x>
  struct _optimize_try_invoke
  {
    using type = x;
  };

  template<class F, class TC, class FC>
  struct _optimize_try_invoke<
    try_invoke<try_invoke<F, TC, FC>, identity, FC>>
  : _optimize_try_invoke<try_invoke<F, TC, FC>>
  {};

  template<class F, class FC>
  struct _optimize_try_invoke<
    try_invoke<try_invoke<F, identity, FC>, identity, FC>>
  : _optimize_try_invoke<try_invoke<F, identity, FC>>
  {};

  template<class F, class TC, class FC>
  struct _optimize_try_invoke<
    try_invoke<try_invoke<F>, TC, FC>>
  : _optimize_try_invoke<try_invoke<F, TC, FC>>
  {};

  template<class F>
  struct _optimize_try_invoke<
    try_invoke<try_invoke<F>>>
  : _optimize_try_invoke<try_invoke<F>>
  {};

  // TODO _optimize_try_invoke<...contract...>


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

  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, contract_barrier<F>>
  {
    using type = valid_contract<F>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, contract_barrier<contract<Pred, C>>>
  {
    using type = contract<Pred, C>;
  };
}
