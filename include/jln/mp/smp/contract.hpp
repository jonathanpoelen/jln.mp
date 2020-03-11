#pragma once

#include "functional/sfinaefwd.hpp"
#include "../functional/try_invoke.hpp"
#include "../functional/function.hpp"
#include "../functional/call.hpp"
#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../number/number.hpp"
#include "../utility/always.hpp"


namespace jln::mp
{
  namespace detail
  {
    template<class C> struct _subcontract;
    template<class x> struct _optimize_try_invoke;
  }

  template<class C>
  struct contract
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<call<C, xs...>>
      ::template f<identity, cfl<violation::template f>, xs...>;
  };

  template<class Pred, class TC = identity, class FC = violation>
  using test_contract = contract<if_<Pred, TC, FC>>;

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<try_invoke<F, TC, FC>>;
  
  using bad_contract = contract<violation>;

  
  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class F, class TC = identity, class FC = violation>
  using try_subcontract = typename detail::_optimize_try_invoke<
    try_invoke<subcontract<F>, TC, FC>>::type;

  
  template<class F>
  struct contract_barrier
  : F
  {};

  template<class F>
  using subcontract_barrier = contract_barrier<subcontract<F>>;
}


namespace jln::mp
{  
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
}

namespace jln::mp::detail
{
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