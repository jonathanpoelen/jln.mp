// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/not_fn.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred>
    struct mk_wrap_in_list_if;

    template<class Pred>
    struct mk_wrap_in_list_if_not;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a \list with the first element if the predicate is checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if = typename detail::mk_wrap_in_list_if_not<
    detail::to_not_fn_t<Pred>
  >::type;

  /// Returns a \list with the first element if the predicate is not checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if_not = typename detail::mk_wrap_in_list_if<
    detail::to_not_fn_t<Pred>
  >::type;

  template<bool b>
  struct wrap_in_list_c;

  template<>
  struct wrap_in_list_c<true>
  : listify
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = list<xs...>;
#endif
  };

  template<>
  struct wrap_in_list_c<false>
  : always<list<>>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f = list<>;
#endif
  };

  template<class b>
  using wrap_in_list = wrap_in_list_c<b::value>;

  namespace emp
  {
    template<class Pred, class... xs>
    using wrap_in_list_if = typename mp::wrap_in_list_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using wrap_in_list_if_not = typename mp::wrap_in_list_if_not<Pred>::template f<xs...>;

    template<class b, class... xs>
    using wrap_in_list = typename mp::wrap_in_list_c<b::value>::template f<xs...>;

    template<bool b, class... xs>
    using wrap_in_list_c = typename mp::wrap_in_list_c<b>::template f<xs...>;
  }
}

#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/utility/enable_if.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/continuation.hpp>
#include <jln/mp/number/not.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct _wrap_in_list_if
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<class Pred>
  struct _wrap_in_list_if_not
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALL_V_TRACE_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<class T>
  struct _wrap_in_list_if<is<T>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_IS_SAME(T, x)>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if<is<T, C>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(C)::template f<number<JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if<is<T, not_<C>>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
        JLN_MP_TRACE_F(C)::template f<number<
          !JLN_MP_IS_SAME(T, x)
        >>::value
      )>
    >::template f<x>;
  };

  template<class T>
  struct _wrap_in_list_if_not<is<T>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<!JLN_MP_IS_SAME(T, x)>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if_not<is<T, C>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
        JLN_MP_TRACE_F(C)::template f<number<JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<class C, class T>
  struct _wrap_in_list_if_not<is<T, not_<C>>>
  {
    template<class x, class... xs>
    using f = typename enable_if_t<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs)),
      wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(
        JLN_MP_TRACE_F(C)::template f<number<!JLN_MP_IS_SAME(T, x)>>::value
      )>
    >::template f<x>;
  };

  template<>
  struct _wrap_in_list_if<same<>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<emp::same_xs_v<x, xs...>>
      ::template f<x>;
  };

  template<class C>
  struct _wrap_in_list_if<same<C>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(
      JLN_MP_TRACE_F(C)::template f<number<emp::same_xs_v<x, xs...>>>::value
    )>::template f<x>;
  };

  template<>
  struct _wrap_in_list_if_not<same<>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<!emp::same_xs_v<x, xs...>>
      ::template f<x>;
  };

  template<class C>
  struct _wrap_in_list_if_not<same<C>>
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_TRACE_F(C)::template f<
      number<!emp::same_xs_v<x, xs...>>
    >::value)>::template f<x>;
  };

#if ! JLN_MP_DEBUG
  template<template<class...> class Pred>
  struct _wrap_in_list_if<cfe<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if_not<cfe<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if<cfl<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::type::value)
    >, x);
  };

  template<template<class...> class Pred>
  struct _wrap_in_list_if_not<cfl<Pred>>
  {
    template<class x, class... xs>
    using f = JLN_MP_CALL_TRACE(wrap_in_list_c<
      JLN_MP_RAW_EXPR_TO_BOOL_NOT(JLN_MP_DCALLF_V_XS(xs, Pred, x, xs...)::type::value)
    >, x);
  };
#endif

  template<class Pred>
  struct mk_wrap_in_list_if
  {
    using type = _wrap_in_list_if<Pred>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if<is<x, not_<>>>
  {
    using type = _wrap_in_list_if_not<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if<same<not_<>>>
  {
    using type = _wrap_in_list_if_not<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if<cfe<F, not_<>>>
  {
    using type = _wrap_in_list_if_not<cfe<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if_not<Pred>;
  };


  template<class x>
  struct mk_wrap_in_list_if_not<is<x, not_<>>>
  {
    using type = _wrap_in_list_if<is<x>>;
  };

  template<>
  struct mk_wrap_in_list_if_not<same<not_<>>>
  {
    using type = _wrap_in_list_if<same<>>;
  };

  template<template<class...> class F>
  struct mk_wrap_in_list_if_not<cfe<F, not_<>>>
  {
    using type = _wrap_in_list_if<cfe<F>>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not<tee<Pred, not_<>>>
  {
    using type = _wrap_in_list_if<Pred>;
  };
}
/// \endcond
