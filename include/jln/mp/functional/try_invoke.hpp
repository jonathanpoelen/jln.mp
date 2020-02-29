#pragma once

#include "function.hpp"
#include "call.hpp"
#include "fork.hpp"
#include "identity.hpp"
#include "if.hpp"
#include "sfinaefwd.hpp"
#include "../number/number.hpp"
#include "../utility/unpack.hpp"
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
    
    template<class x>
    struct _try_invoke_dispatch;
  }

  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class C>
  using assume_number = typename detail::_assume_number<subcontract<C>>::type;

  template<class C>
  using assume_unary = typename detail::_assume_unary<subcontract<C>>::type;

  template<class F, class TC = identity, class FC = violation>
  struct try_invoke;

  template<class C>
  struct contract
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<call<C, xs...>>
      ::template f<identity, cfl<violation::template f>, xs...>;
  };

  using bad_contract = contract<violation>;
  
  template<class Pred, class TC = identity, class FC = violation>
  using test_contract = contract<if_<Pred, TC, FC>>;

  template<class F, class FC>
  using try_invoke_or = try_invoke<F, identity, FC>;

  template<class C, class TC, class FC>
  struct try_invoke<contract<C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<call<C, xs...>>
      ::template f<TC, FC, xs...>;
  };

  template<class C>
  struct try_invoke<contract<C>, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na, call<C, xs...>>::value>;
  };

  template<class F, class TC, class FC>
  struct try_invoke
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<
      decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>::template f<TC, FC, xs...>;
  };

  template<class F>
  struct try_invoke<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na, decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>::value>;
  };

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<try_invoke<F, TC, FC>>;

  namespace emp
  {
    template<class L, class F, class TC = mp::identity, class FC = mp::violation>
    using try_invoke = unpack<L, try_invoke<F, TC, FC>>;
  }

  template<class F>
  struct contract_barrier 
  : F
  {};

  template<class F>
  using subcontract_barrier = contract_barrier<subcontract<F>>;

  template<class F, class TC = identity, class FC = violation>
  using try_subcontract = typename detail::_optimize_try_invoke<
    try_invoke<subcontract<F>, TC, FC>>::type;
}


#include "../number/as_number.hpp"

namespace jln::mp::detail
{
  template<class x>
  struct _try_invoke_dispatch
  {
    template<class TC, class FC, class...>
    using f = typename TC::template f<x>;
  };
  
  template<>
  struct _try_invoke_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };
  
  // for reduce recursivity
  // TODO subcontract_for_unary
  // TODO subcontract_for_binary
  // TODO subcontract_for_list

  template<class F>
  struct _subcontract
  {
    using type = try_invoke<F>;
  };

  template<class C>
  struct _subcontract<contract<C>>
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


  template<class F>
  typename F::type lazy_build(int);

  template<class F>
  bad_contract lazy_build(...);

#define JLN_MP_PARAM_NAME_2(name, init) name
#define JLN_MP_PARAM_NAME_1(name) name

#define JLN_MP_PARAM_DECL_2(name, init) name = init
#define JLN_MP_PARAM_DECL_1(name) name

#define JLN_MP_PARAM_COUNT_I(a, b, c, ...) c
#define JLN_MP_PARAM_COUNT(...) JLN_MP_PARAM_COUNT_I(__VA_ARGS__, _2, _1, _0)

#define JLN_MP_PP_CAT_I(a, b) a##b
#define JLN_MP_PP_CAT(a, b) JLN_MP_PP_CAT_I(a, b)

#define JLN_MP_PARAM_DECL(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_DECL, JLN_MP_PARAM_COUNT arg) arg
#define JLN_MP_PARAM_NAME(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_NAME, JLN_MP_PARAM_COUNT arg) arg

#define JLN_MP_MAKE_REGULAR_SMP1_II(                     \
  ns_smp, ns_detail, smp_name, name, na, da, ...)        \
  namespace ns_detail {                                  \
    template<class na, class = void>                     \
    struct smp_name {};                                  \
    template<class na>                                   \
    struct smp_name<na, std::void_t<__VA_ARGS__>>        \
    { using type = __VA_ARGS__; };                       \
  }                                                      \
  namespace ns_smp {                                     \
    template<class da>                                   \
    using name = decltype(::jln::mp::detail::lazy_build< \
      ::ns_detail::smp_name<na>>(1));                    \
  }

#define JLN_MP_MAKE_REGULAR_SMP1_I(ns_smp, ns_detail, smp_name, name, na, da, ...) \
  JLN_MP_MAKE_REGULAR_SMP1_II(ns_smp, ns_detail, smp_name, name, na, da, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP1(ns_smp, ns_detail, smp_name, name, a, ...) \
  JLN_MP_MAKE_REGULAR_SMP1_I(ns_smp, ns_detail, smp_name, name,             \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_DECL(a), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP1_P(name, a, ...) JLN_MP_MAKE_REGULAR_SMP1( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2_II(                      \
  ns_smp, ns_detail, smp_name, name, na, nb, da, db, ...) \
  namespace ns_detail {                                   \
    template<class na, class nb, class = void>            \
    struct smp_name {};                                   \
    template<class na, class nb>                          \
    struct smp_name<na, nb, std::void_t<__VA_ARGS__>>     \
    { using type = __VA_ARGS__; };                        \
  }                                                       \
  namespace ns_smp {                                      \
    template<class da, class db>                          \
    using name = decltype(::jln::mp::detail::lazy_build<  \
      ::ns_detail::smp_name<na, nb>>(1));                 \
  }

#define JLN_MP_MAKE_REGULAR_SMP2_I(ns_smp, ns_detail, smp_name, name, na, nb, da, db, ...) \
  JLN_MP_MAKE_REGULAR_SMP2_II(ns_smp, ns_detail, smp_name, name, na, nb, da, db, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2(ns_smp, ns_detail, smp_name, name, a, b, ...) \
  JLN_MP_MAKE_REGULAR_SMP2_I(ns_smp, ns_detail, smp_name, name,                \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP2_P(name, a, b, ...) JLN_MP_MAKE_REGULAR_SMP2( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, __VA_ARGS__)


#define JLN_MP_MAKE_REGULAR_SMP3_II(                              \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, ...) \
  namespace ns_detail {                                           \
    template<class na, class nb, class nc, class = void>          \
    struct smp_name {};                                           \
    template<class na, class nb, class nc>                        \
    struct smp_name<na, nb, nc, std::void_t<__VA_ARGS__>>         \
    { using type = __VA_ARGS__; };                                \
  }                                                               \
  namespace ns_smp {                                              \
    template<class da, class db, class dc>                        \
    using name = decltype(::jln::mp::detail::lazy_build<          \
      ::ns_detail::smp_name<na, nb, nc>>(1));                     \
  }

#define JLN_MP_MAKE_REGULAR_SMP3_I(                               \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, ...) \
  JLN_MP_MAKE_REGULAR_SMP3_II(                                    \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, da, db, dc, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP3(ns_smp, ns_detail, smp_name, name, a, b, c, ...) \
  JLN_MP_MAKE_REGULAR_SMP3_I(ns_smp, ns_detail, smp_name, name,                   \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b), JLN_MP_PARAM_NAME(c),             \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b), JLN_MP_PARAM_DECL(c), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP3_P(name, a, b, c, ...) JLN_MP_MAKE_REGULAR_SMP3( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, __VA_ARGS__)


#define JLN_MP_MAKE_REGULAR_SMP4_II(                                      \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, ...) \
  namespace ns_detail {                                                   \
    template<class na, class nb, class nc, class nd, class = void>        \
    struct smp_name {};                                                   \
    template<class na, class nb, class nc, class nd>                      \
    struct smp_name<na, nb, nc, nd, std::void_t<__VA_ARGS__>>             \
    { using type = __VA_ARGS__; };                                        \
  }                                                                       \
  namespace ns_smp {                                                      \
    template<class da, class db, class dc, class dd>                      \
    using name = decltype(::jln::mp::detail::lazy_build<                  \
      ::ns_detail::smp_name<na, nb, nc, nd>>(1));                         \
  }

#define JLN_MP_MAKE_REGULAR_SMP4_I(                                       \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, ...) \
  JLN_MP_MAKE_REGULAR_SMP4_II(                                            \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, da, db, dc, dd, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP4(ns_smp, ns_detail, smp_name, name, a, b, c, d, ...) \
  JLN_MP_MAKE_REGULAR_SMP4_I(ns_smp, ns_detail, smp_name, name,                      \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                      \
    JLN_MP_PARAM_NAME(c), JLN_MP_PARAM_NAME(d),                                      \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b),                                      \
    JLN_MP_PARAM_DECL(c), JLN_MP_PARAM_DECL(d), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP4_P(name, a, b, c, d, ...) JLN_MP_MAKE_REGULAR_SMP4( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, d, __VA_ARGS__)


  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, contract<C>>
  {
    using type = contract<C>;
  };

  template<template<class> class sfinae, class F, class TC, class FC>
  struct _sfinae<sfinae, try_invoke<F, TC, FC>>
  {
    using type = contract<try_invoke<F, TC, FC>>;
  };

  template<template<class> class sfinae, class F>
  struct _sfinae<sfinae, contract_barrier<F>>
  {
    using type = contract<F>;
  };
}
