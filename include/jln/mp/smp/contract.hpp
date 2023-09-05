// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/sfinaefwd.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/utility/conditional.hpp>


namespace jln::mp
{
  namespace detail
  {
    template<class C> struct _subcontract;
    template<class x> struct _try_subcontract;
  }

  template<class C>
  struct contract
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };

  template<class test, class TC, class FC = violation>
  using contract_if = typename conditional_c<test::value>::template f<TC, FC>;

  template<bool test, class TC, class FC = violation>
  using contract_if_c = typename conditional_c<test>::template f<TC, FC>;

  template<class Pred, class TC = identity, class FC = violation>
  using test_contract = contract<if_<Pred, TC, FC>>;

  template<class F, class TC = identity, class FC = violation>
  using try_contract = contract<try_<F, TC, FC>>;

  using bad_contract = contract<violation>;


  template<class C>
  using subcontract = typename detail::_subcontract<C>::type;

  template<class F, class TC = identity, class FC = violation>
  using try_subcontract = typename detail::_try_subcontract<F>::template f<TC, FC>;

  template<class F>
  using subcontract_barrier = contract<subcontract<F>>;
}


namespace jln::mp
{
  /// \cond
  template<class C, class TC, class FC>
  struct try_<contract<C>, TC, FC>
  {
    template<class... xs>
    using f = typename detail::_try_dispatch<JLN_MP_DCALL_TRACE_XS(xs, C, xs...)>
      ::template f<TC, FC, xs...>;
  };

  template<class C>
  struct try_<contract<C>, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na, JLN_MP_DCALL_TRACE_XS(xs, C, xs...)>::value>;
  };

  template<class C>
  struct try_<contract<C>, identity, violation>
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, xs...);
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct _subcontract
  {
    using type = try_<F>;
  };

  template<class C>
  struct _subcontract<contract<C>>
  {
    using type = C;
  };

  template<class F, class TC, class FC>
  struct _subcontract<try_<F, TC, FC>>
  {
    using type = try_<F, TC, FC>;
  };

  template<class F>
  struct optimize_try
  {
    using type = F;
  };

  template<class F>
  struct _try_subcontract
  {
    template<class TC, class FC>
    using f = try_<F, TC, FC>;
  };

  template<class TC, class FC>
  struct _try_subcontract_contract
  {
    template<class F>
    using f = typename optimize_try<try_<F, TC, FC>>::type;
  };

  template<>
  struct _try_subcontract_contract<identity, violation>
  {
    template<class F>
    using f = F;
  };

  template<class F>
  struct _try_subcontract<contract<F>>
  {
    template<class TC, class FC>
    using f = typename _try_subcontract_contract<TC, FC>::template f<F>;
  };

  template<class F, class TC1, class FC1>
  struct _try_subcontract<try_<F, TC1, FC1>>
  {
    template<class TC, class FC>
    using f = typename optimize_try<try_<try_<F, TC1, FC1>, TC, FC>>::type;
  };

  template<class F, class TC, class FC, class FC2>
  struct optimize_try<try_<try_<F, TC, FC>, identity, FC2>>
  : optimize_try<try_<F, TC, FC>>
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
#define JLN_MP_PARAM_COUNT_P(...) (__VA_ARGS__, _2, _1, _0)
#define JLN_MP_PARAM_COUNT(arg) JLN_MP_IDENT(JLN_MP_PARAM_COUNT_I JLN_MP_PARAM_COUNT_P arg)

#define JLN_MP_PP_CAT_II(a, b) a##b
#define JLN_MP_PP_CAT_I(a, b) JLN_MP_PP_CAT_II(a,b)
#define JLN_MP_PP_CAT(a, b) JLN_MP_PP_CAT_I(a, b)

#define JLN_MP_PARAM_DECL(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_DECL, JLN_MP_PARAM_COUNT(arg)) arg
#define JLN_MP_PARAM_NAME(arg) JLN_MP_PP_CAT(JLN_MP_PARAM_NAME, JLN_MP_PARAM_COUNT(arg)) arg

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


#define JLN_MP_MAKE_REGULAR_SMP5_II(                                              \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, ...) \
  namespace ns_detail {                                                           \
    template<class na, class nb, class nc, class nd, class ne, class = void>      \
    struct smp_name {};                                                           \
    template<class na, class nb, class nc, class nd, class ne>                    \
    struct smp_name<na, nb, nc, nd, ne, std::void_t<__VA_ARGS__>>                 \
    { using type = __VA_ARGS__; };                                                \
  }                                                                               \
  namespace ns_smp {                                                              \
    template<class da, class db, class dc, class dd, class de>                    \
    using name = decltype(::jln::mp::detail::lazy_build<                          \
      ::ns_detail::smp_name<na, nb, nc, nd, ne>>(1));                             \
  }

#define JLN_MP_MAKE_REGULAR_SMP5_I(                                               \
  ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, ...) \
  JLN_MP_MAKE_REGULAR_SMP5_II(                                                    \
    ns_smp, ns_detail, smp_name, name, na, nb, nc, nd, ne, da, db, dc, dd, de, __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP5(ns_smp, ns_detail, smp_name, name, a, b, c, d, e, ...) \
  JLN_MP_MAKE_REGULAR_SMP5_I(ns_smp, ns_detail, smp_name, name,                         \
    JLN_MP_PARAM_NAME(a), JLN_MP_PARAM_NAME(b),                                         \
    JLN_MP_PARAM_NAME(c), JLN_MP_PARAM_NAME(d),                                         \
    JLN_MP_PARAM_NAME(e),                                                               \
    JLN_MP_PARAM_DECL(a), JLN_MP_PARAM_DECL(b),                                         \
    JLN_MP_PARAM_DECL(c), JLN_MP_PARAM_DECL(d),                                         \
    JLN_MP_PARAM_DECL(e), __VA_ARGS__)

#define JLN_MP_MAKE_REGULAR_SMP5_P(name, a, b, c, d, e, ...) JLN_MP_MAKE_REGULAR_SMP5( \
  jln::mp::smp, jln::mp::detail, smp_##name, name, a, b, c, d, e, __VA_ARGS__)


  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, contract<C>>
  {
    using type = contract<C>;
  };

  template<template<class> class sfinae, class F, class TC, class FC>
  struct _sfinae<sfinae, try_<F, TC, FC>>
  {
    using type = contract<try_<F, TC, FC>>;
  };
}
/// \endcond
