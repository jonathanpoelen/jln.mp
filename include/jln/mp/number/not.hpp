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
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>);
  };

  template<class C>
  struct not_<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>);
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using not_ = typename mp::not_<C>::template f<x>;

    template<class x, class C = mp::identity>
    inline constexpr bool not_v = mp::not_<C>::template f<x>::value;
  }
}


#include <jln/mp/number/as_bool.hpp>
#include <jln/mp/number/to_bool.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/algorithm/same.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/list/size.hpp>

#if JLN_MP_CUDA
#  include <cstddef>
#endif

/// \cond
namespace jln::mp
{
  template<>
  struct not_<identity>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>;
  };

  template<>
  struct not_<not_<identity>>
  {
    template<class x>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL(x::value)>;
  };

#if JLN_MP_CUDA
#  define JLN_MP_AS_BOOL(v) std::enable_if_t<std::size_t{v} <= 1, bool>{v}
#else
#  define JLN_MP_AS_BOOL(v) JLN_MP_INTEGRAL_AS(bool, v)
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
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>;
  };

  template<class C>
  struct to_bool<not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(x::value)>);
  };

  template<class T, class C>
  struct is<T, not_<C>>
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_IS_SAME(T, x)>);
  };

  template<class T>
  struct is<T, not_<>>
  {
    template<class x>
    using f = number<!JLN_MP_IS_SAME(T, x)>;
  };

  template<class C>
  struct same<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C,
      number<!emp::same_xs_v<xs...>>
    );
  };

  template<>
  struct same<not_<>>
  {
    template<class... xs>
    using f = number<!emp::same_xs_v<xs...>>;
  };

  template<class C>
  struct size<not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>);
  };

  template<>
  struct size<not_<>>
  {
    template<class... xs>
    using f = number<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>;
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
    using f = typename mp::conditional_c<JLN_MP_RAW_EXPR_TO_BOOL_NOT(sizeof...(xs))>
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

  template<class C, class TC, class FC>
  struct if_<same<not_<C>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      JLN_MP_TRACE_F(C)::template f<number<
        !emp::same_xs_v<xs...>
      >>::value
    >
      ::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
      ::template f<xs...>;
  };

  template<class TC, class FC>
  struct if_<same<not_<>>, TC, FC> : if_<same<>, FC, TC>
  {};

  template<class x, class TC, class FC>
  struct if_<is<x, not_<>>, TC, FC> : if_<is<x>, FC, TC>
  {};
}

/// \endcond
