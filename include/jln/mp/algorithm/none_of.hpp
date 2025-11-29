// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate does not hold for any element of a \sequence.
  /// \c none_of is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `none_of<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// If the predicate is fast, short-circuiting can slow down evaluation,
  /// and this form may be faster: `transform<Pred, none_of<is<true_>, C>>`
  /// because \c none_of is optimized with \c is.
  /// \treturn \bool
  /// \see all_of, any_of
  template<class Pred, class C = identity>
  struct none_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  /// Checks whether a predicate holds for all elements of a \sequence.
  /// \c all_of is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == false`, then instantiating
  /// `all_of<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// If the predicate is fast, short-circuiting can slow down evaluation,
  /// and this form may be faster: `transform<Pred, all_of<is<true_>, C>>`
  /// because \c all_of is optimized with \c is.
  /// \treturn \bool
  /// \see any_of, none_of
  template<class Pred, class C = identity>
  struct all_of
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      typename detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type
    );
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = typename detail::_unpack<mp::none_of<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using none_of_xs = typename mp::none_of<Pred>::template f<xs...>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool none_of_v = detail::_unpack<L, mp::none_of<Pred, C>, L>::type::value;

    template<class Pred, class... xs>
    inline constexpr bool none_of_xs_v = mp::none_of<Pred>::template f<xs...>::value;


    template<class L, class Pred, class C = mp::identity>
    using all_of = typename detail::_unpack<mp::all_of<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using all_of_xs = typename mp::all_of<Pred>::template f<xs...>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool all_of_v = detail::_unpack<mp::all_of<Pred, C>, L>::type::value;

    template<class Pred, class... xs>
    inline constexpr bool all_of_xs_v = mp::all_of<Pred>::template f<xs...>::value;
  }
} // namespace jln::mp

#include <jln/mp/number/not.hpp>
#include <jln/mp/utility/is.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/functional/if.hpp>

/// \cond
namespace jln::mp
{
  template<class Pred>
  struct none_of<Pred>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct none_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct none_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };


  template<class Pred>
  struct all_of<Pred>
  {
    template<class... xs>
    using f = typename detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type;
  };

  template<class Pred>
  struct all_of<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!detail::is_drop_while_continue<
      typename detail::_drop_while<sizeof...(xs)>
      ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
    >::type::value>;
  };

  template<class Pred, class C>
  struct all_of<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(
      C,
      number<!detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value>
    );
  };


  /*
   * Pred = is<T>
   */

  template<class T>
  struct none_of<is<T>>
  {
    template<class... xs>
    using f = number<JLN_MP_NONE_SAME_AS(T, xs)>;
  };

  template<class T, class C>
  struct none_of<is<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_NONE_SAME_AS(T, xs)>);
  };

  template<class T>
  struct none_of<is<T>, not_<>>
  {
    template<class... xs>
    using f = number<!JLN_MP_NONE_SAME_AS(T, xs)>;
  };

  template<class T, class C>
  struct none_of<is<T>, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_NONE_SAME_AS(T, xs)>);
  };


  template<class T>
  struct all_of<is<T>>
  {
    template<class... xs>
    using f = number<JLN_MP_ALL_SAME_AS(T, xs)>;
  };

  template<class T, class C>
  struct all_of<is<T>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<JLN_MP_ALL_SAME_AS(T, xs)>);
  };

  template<class T>
  struct all_of<is<T>, not_<>>
  {
    template<class... xs>
    using f = number<!JLN_MP_ALL_SAME_AS(T, xs)>;
  };

  template<class T, class C>
  struct all_of<is<T>, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!JLN_MP_ALL_SAME_AS(T, xs)>);
  };


  /*
   * Pred = is<T, not_<C>>
   */

  template<class T, class NC>
  struct none_of<is<T, not_<NC>>>
    : all_of<is<T, NC>>
  {};

  template<class T, class NC, class C>
  struct none_of<is<T, not_<NC>>, C>
    : all_of<is<T, NC>, C>
  {};

  template<class T, class NC>
  struct none_of<is<T, not_<NC>>, not_<>>
    : all_of<is<T, NC>, not_<>>
  {};

  template<class T, class NC, class C>
  struct none_of<is<T, not_<NC>>, not_<C>>
    : all_of<is<T, NC>, not_<NC>>
  {};


  template<class T, class NC>
  struct all_of<is<T, not_<NC>>>
    : none_of<is<T, NC>>
  {};

  template<class T, class NC, class C>
  struct all_of<is<T, not_<NC>>, C>
    : none_of<is<T, NC>, C>
  {};

  template<class T, class NC>
  struct all_of<is<T, not_<NC>>, not_<>>
    : none_of<is<T, NC>, not_<>>
  {};

  template<class T, class NC, class C>
  struct all_of<is<T, not_<NC>>, not_<C>>
    : none_of<is<T, NC>, not_<NC>>
  {};


  /*
   * Pred = is_list<>
   */

#if !JLN_MP_GCC
  template<>
  struct all_of<is_list<>>
  {
    template<class... xs>
    using f = number<(emp::is_list_v<xs> && ... && true)>;
  };

  template<class C>
  struct all_of<is_list<>, C>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<(emp::is_list_v<xs> && ... && true)>);
  };

  template<>
  struct all_of<is_list<>, not_<>>
  {
    template<class... xs>
    using f = number<!(emp::is_list_v<xs> && ... && true)>;
  };

  template<class C>
  struct all_of<is_list<>, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!(emp::is_list_v<xs> && ... && true)>);
  };
#endif


  /*
   * If
   */

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<none_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_until<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };


  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !detail::is_drop_while_continue<
        typename detail::_drop_while<sizeof...(xs)>
        ::template f<0, JLN_MP_TRACE_F(Pred), xs...>
      >::type::value
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
} // namespace jln::mp
/// \endcond
