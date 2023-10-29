// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup number

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!x::value)>);
  };

  template<class C>
  struct not_<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<(!int_{!x::value})>);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using not_ = typename mp::not_<C>::template f<x>;
  }
}

/// \cond
#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/list/size.hpp>

namespace jln::mp
{
  template<>
  struct not_<identity>
  {
    template<class x>
    using f = number<(!x::value)>;
  };

#if JLN_MP_CUDA
#  define JLN_MP_AS_BOOL(v) std::enable_if_t<std::size_t{v} <= 1, bool>{v}
#else
#  define JLN_MP_AS_BOOL(v) bool{v}
#endif

  template<>
  struct as_bool<not_<>>
  {
    template<class x>
    using f = number<!JLN_MP_AS_BOOL(x::value)>;
  };

  template<class C>
  struct as_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_AS_BOOL(x::value)>);
  };

#undef JLN_MP_AS_BOOL

  template<>
  struct to_bool<not_<>>
  {
    template<class x>
    using f = number<!bool(x::value)>;
  };

  template<class C>
  struct to_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!bool(x::value)>);
  };

  template<class T, class C>
  struct is<T, not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!std::is_same<T, x>::value>);
  };

  template<class T>
  struct is<T, not_<>>
  {
    template<class x>
    using f = number<!std::is_same<T, x>::value>;
  };

  template<class C>
  struct size<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!sizeof...(xs)>);
  };

  template<>
  struct size<not_<>>
  {
    template<class... xs>
    using f = number<!sizeof...(xs)>;
  };

  template<int_ i, class C>
  struct size<is<number<i>, not_<C>>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sizeof...(xs) != i>);
  };

  template<int_ i>
  struct size<is<number<i>, not_<>>>
  {
    template<class... xs>
    using f = number<sizeof...(xs) != i>;
  };

  template<class TC, class FC>
  struct if_<size<not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<!sizeof...(xs)>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<int_ i, class TC, class FC>
  struct if_<size<is<number<i>, not_<>>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<sizeof...(xs) != i>
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };
}

/// \endcond
