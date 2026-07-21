// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/number/not.hpp>
#include <jln/mp/algorithm/drop_until.hpp>
#include <jln/mp/functional/sfinae_truthy_falsy.hpp>

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
  /// When the concepts are available and the predicate cannot fail,
  /// \c none_of_sfinae_truthy will be faster.
  /// \semantics
  ///   \code
  ///   none_of<greater_than_c<5>>::f<> == true_
  ///   none_of<greater_than_c<5>>::f<number<0>, number<2>, number<4>> == true_
  ///   none_of<greater_than_c<5>>::f<number<0>, number<2>, number<10>> == false_
  ///   \endcode
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
  /// When the concepts are available and the predicate cannot fail,
  /// \c all_of_sfinae_truthy will be faster.
  /// \semantics
  ///   \code
  ///   all_of<greater_than_c<5>>::f<> == true_
  ///   all_of<greater_than_c<5>>::f<number<10>, number<12>, number<4>> == false_
  ///   all_of<greater_than_c<5>>::f<number<10>, number<12>, number<14>> == true_
  ///   \endcode
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

  /// Checks whether a predicate holds for at least some element of a \sequence.
  /// \c any_of is short-circuiting: if there is a template type
  /// argument `xs[i]` with `bool(xs[i]::value) == true`, then instantiating
  /// `any_of<C>::f<xs[0], ..., xs[n-1]>` does not require the
  /// instantiation of `Pred::f<xs[j]>::value` for `j > i`.
  /// If the predicate is fast, short-circuiting can slow down evaluation,
  /// and this form may be faster: `transform<Pred, any_of<is<true_>, C>>`
  /// because \c any_of is optimized with \c is.
  /// When the concepts are available and the predicate cannot fail,
  /// \c any_of_sfinae_truthy will be faster.
  /// \semantics
  ///   \code
  ///   any_of<greater_than_c<5>>::f<> == false_
  ///   any_of<greater_than_c<5>>::f<number<0>, number<2>, number<4>> == false_
  ///   any_of<greater_than_c<5>>::f<number<0>, number<12>, number<4>> == true_
  ///   \endcode
  /// \treturn \bool
  /// \see all_of, none_of
  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;

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


    template<class L, class Pred, class C = mp::identity>
    using any_of = typename detail::_unpack<mp::any_of<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using any_of_xs = typename mp::any_of<Pred>::template f<xs...>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool any_of_v = detail::_unpack<mp::any_of<Pred, C>, L>::type::value;

    template<class Pred, class... xs>
    inline constexpr bool any_of_xs_v = mp::any_of<Pred>::template f<xs...>::value;
  }

#if JLN_MP_FEATURE_CONCEPTS
  namespace emp
  {
    template<class Pred, class... xs>
    inline constexpr bool any_of_sfinae_truthy_xs_v
      = requires { requires (sfinae_truthy_as<Pred, xs> || ...); };

    template<class Pred, class... xs>
    inline constexpr bool any_of_sfinae_falsy_xs_v
      = requires { requires (sfinae_falsy_as<Pred, xs> || ...); };

    template<class Pred, class... xs>
    inline constexpr bool all_of_sfinae_truthy_xs_v
      = requires { requires (sfinae_truthy_as<Pred, xs> && ...); };

    template<class Pred, class... xs>
    inline constexpr bool all_of_sfinae_falsy_xs_v
      = requires { requires (sfinae_falsy_as<Pred, xs> && ...); };

    template<class Pred, class... xs>
    inline constexpr bool none_of_sfinae_truthy_xs_v = !any_of_sfinae_truthy_xs_v<Pred, xs...>;

    template<class Pred, class... xs>
    inline constexpr bool none_of_sfinae_falsy_xs_v = !any_of_sfinae_falsy_xs_v<Pred, xs...>;
  }

  /// Checks whether \c sfinae_truthy_as holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   any_of_sfinae_truthy<greater_than_c<5>>::f<> == false_
  ///   any_of_sfinae_truthy<greater_than_c<5>>::f<number<0>, number<2>> == false_
  ///   any_of_sfinae_truthy<greater_than_c<5>>::f<number<0>, number<12>> == true_
  ///   any_of_sfinae_truthy<greater_than_c<5>>::f<void, number<12>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see any_of, any_of_sfinae_falsy, all_of_sfinae_truthy, none_of_sfinae_truthy
  template<class Pred, class C = identity>
  struct any_of_sfinae_truthy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::any_of_sfinae_truthy_xs_v<Pred, xs...>>);
  };

  /// Checks whether \c sfinae_falsy_as holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   any_of_sfinae_falsy<greater_than_c<5>>::f<> == false_
  ///   any_of_sfinae_falsy<greater_than_c<5>>::f<number<0>, number<12>> == false_
  ///   any_of_sfinae_falsy<greater_than_c<5>>::f<number<0>, number<2>> == true_
  ///   any_of_sfinae_falsy<greater_than_c<5>>::f<void, number<2>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see any_of, any_of_sfinae_truthy, all_of_sfinae_falsy, none_of_sfinae_falsy
  template<class Pred, class C = identity>
  struct any_of_sfinae_falsy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::any_of_sfinae_falsy_xs_v<Pred, xs...>>);
  };

  /// Checks whether \c sfinae_truthy_as holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   all_of_sfinae_truthy<greater_than_c<5>>::f<> == true_
  ///   all_of_sfinae_truthy<greater_than_c<5>>::f<number<10>, number<4>> == false_
  ///   all_of_sfinae_truthy<greater_than_c<5>>::f<number<10>, number<14>> == true_
  ///   all_of_sfinae_truthy<greater_than_c<5>>::f<void, number<14>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see all_of, all_of_sfinae_falsy, any_of_sfinae_truthy, none_of_sfinae_truthy
  template<class Pred, class C = identity>
  struct all_of_sfinae_truthy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::all_of_sfinae_truthy_xs_v<Pred, xs...>>);
  };

  /// Checks whether \c sfinae_falsy_as holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   all_of_sfinae_falsy<greater_than_c<5>>::f<> == true_
  ///   all_of_sfinae_falsy<greater_than_c<5>>::f<number<10>, number<4>> == false_
  ///   all_of_sfinae_falsy<greater_than_c<5>>::f<number<1>, number<4>> == true_
  ///   all_of_sfinae_falsy<greater_than_c<5>>::f<void, number<4>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see all_of, all_of_sfinae_truthy, any_of_sfinae_falsy, none_of_sfinae_falsy
  template<class Pred, class C = identity>
  struct all_of_sfinae_falsy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::all_of_sfinae_falsy_xs_v<Pred, xs...>>);
  };


  /// Checks whether \c sfinae_truthy_as does not holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   none_of_sfinae_truthy<greater_than_c<5>>::f<> == true_
  ///   none_of_sfinae_truthy<greater_than_c<5>>::f<number<2>, number<10>> == false_
  ///   none_of_sfinae_truthy<greater_than_c<5>>::f<number<2>, number<4>> == true_
  ///   none_of_sfinae_truthy<greater_than_c<5>>::f<void, number<4>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see none_of, none_of_sfinae_falsy, any_of_sfinae_truthy, all_of_sfinae_truthy
  template<class Pred, class C = identity>
  using none_of_sfinae_truthy = any_of_sfinae_truthy<Pred, not_<C>>;

  /// Checks whether \c sfinae_falsy_as does not holds for all elements of a \sequence.
  /// \semantics
  ///   \code
  ///   none_of_sfinae_falsy<greater_than_c<5>>::f<> == true_
  ///   none_of_sfinae_falsy<greater_than_c<5>>::f<number<2>, number<10>> == false_
  ///   none_of_sfinae_falsy<greater_than_c<5>>::f<number<12>, number<10>> == true_
  ///   none_of_sfinae_falsy<greater_than_c<5>>::f<void, number<10>> == false_
  ///   \endcode
  /// \treturn \bool
  /// \see none_of, none_of_sfinae_truthy, any_of_sfinae_falsy, all_of_sfinae_falsy
  template<class Pred, class C = identity>
  using none_of_sfinae_falsy = any_of_sfinae_falsy<Pred, not_<C>>;


  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of_sfinae_truthy = typename detail::_unpack<mp::any_of_sfinae_truthy<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using any_of_sfinae_truthy_xs = number<any_of_sfinae_truthy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool any_of_sfinae_truthy_v
      = detail::_unpack<mp::any_of_sfinae_truthy<Pred, C>, L>::type::value;


    template<class L, class Pred, class C = mp::identity>
    using any_of_sfinae_falsy = typename detail::_unpack<mp::any_of_sfinae_falsy<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using any_of_sfinae_falsy_xs = number<any_of_sfinae_falsy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool any_of_sfinae_falsy_v
      = detail::_unpack<mp::any_of_sfinae_falsy<Pred, C>, L>::type::value;


    template<class L, class Pred, class C = mp::identity>
    using all_of_sfinae_truthy = typename detail::_unpack<mp::all_of_sfinae_truthy<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using all_of_sfinae_truthy_xs = number<all_of_sfinae_truthy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool all_of_sfinae_truthy_v
      = detail::_unpack<mp::all_of_sfinae_truthy<Pred, C>, L>::type::value;


    template<class L, class Pred, class C = mp::identity>
    using all_of_sfinae_falsy = typename detail::_unpack<mp::all_of_sfinae_falsy<Pred, C>, L>::type;

    template<class Pred, class... xs>
    using all_of_sfinae_falsy_xs = number<all_of_sfinae_falsy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool all_of_sfinae_falsy_v
      = detail::_unpack<mp::all_of_sfinae_falsy<Pred, C>, L>::type::value;


    template<class L, class Pred, class C = mp::identity>
    using none_of_sfinae_truthy = any_of_sfinae_truthy<L, Pred, mp::not_<C>>;

    template<class Pred, class... xs>
    using none_of_sfinae_truthy_xs = number<!any_of_sfinae_truthy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool none_of_sfinae_truthy_v = any_of_sfinae_truthy_v<L, Pred, mp::not_<C>>;


    template<class L, class Pred, class C = mp::identity>
    using none_of_sfinae_falsy = any_of_sfinae_falsy<L, Pred, mp::not_<C>>;

    template<class Pred, class... xs>
    using none_of_sfinae_falsy_xs = number<!any_of_sfinae_falsy_xs_v<Pred, xs...>>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool none_of_sfinae_falsy_v = any_of_sfinae_falsy_v<L, Pred, mp::not_<C>>;
  }
#endif

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


#if JLN_MP_FEATURE_CONCEPTS
  /*
   * any_of_sfinae_*
   */

  template<class Pred>
  struct any_of_sfinae_truthy<Pred>
  {
    template<class... xs>
    using f = number<emp::any_of_sfinae_truthy_xs_v<Pred, xs...>>;
  };

  template<class Pred>
  struct any_of_sfinae_falsy<Pred>
  {
    template<class... xs>
    using f = number<emp::any_of_sfinae_falsy_xs_v<Pred, xs...>>;
  };

  /*
   * none_of_sfinae_*
   */

  template<class Pred>
  struct any_of_sfinae_truthy<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!emp::any_of_sfinae_truthy_xs_v<Pred, xs...>>;
  };

  template<class Pred>
  struct any_of_sfinae_falsy<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!emp::any_of_sfinae_falsy_xs_v<Pred, xs...>>;
  };

  template<class Pred, class C>
  struct any_of_sfinae_truthy<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!emp::any_of_sfinae_truthy_xs_v<Pred, xs...>>);
  };

  template<class Pred, class C>
  struct any_of_sfinae_falsy<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<!emp::any_of_sfinae_falsy_xs_v<Pred, xs...>>);
  };

  /*
   * all_of_sfinae_*
   */

  template<class Pred>
  struct all_of_sfinae_truthy<Pred>
  {
    template<class... xs>
    using f = number<emp::all_of_sfinae_truthy_xs_v<Pred, xs...>>;
  };

  template<class Pred>
  struct all_of_sfinae_falsy<Pred>
  {
    template<class... xs>
    using f = number<emp::all_of_sfinae_falsy_xs_v<Pred, xs...>>;
  };

  template<class Pred>
  struct all_of_sfinae_truthy<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!emp::all_of_sfinae_truthy_xs_v<Pred, xs...>>;
  };

  template<class Pred>
  struct all_of_sfinae_falsy<Pred, not_<>>
  {
    template<class... xs>
    using f = number<!emp::all_of_sfinae_falsy_xs_v<Pred, xs...>>;
  };

  template<class Pred, class C>
  struct all_of_sfinae_truthy<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::all_of_sfinae_truthy_xs_v<Pred, xs...>>);
  };

  template<class Pred, class C>
  struct all_of_sfinae_falsy<Pred, not_<C>>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<emp::all_of_sfinae_falsy_xs_v<Pred, xs...>>);
  };

  /*
   * Pred = is<T>
   */

  template<class T> struct any_of_sfinae_truthy<is<T>>
    : none_of<is<T>, not_<>> {};
  template<class T> struct any_of_sfinae_truthy<is<T>, not_<>>
    : none_of<is<T>> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T>, C>
    : none_of<is<T>, not_<C>> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T>, not_<C>>
    : none_of<is<T>, C> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T>, not_<not_<C>>>
    : none_of<is<T>, not_<C>> {};

  template<class T> struct all_of_sfinae_truthy<is<T>>
    : all_of<is<T>> {};
  template<class T> struct all_of_sfinae_truthy<is<T>, not_<>>
    : all_of<is<T>, not_<>> {};
  template<class T, class C> struct all_of_sfinae_truthy<is<T>, C>
    : all_of<is<T>, C> {};
  template<class T, class C> struct all_of_sfinae_truthy<is<T>, not_<C>>
    : all_of<is<T>, not_<C>> {};

  template<class T> struct any_of_sfinae_falsy<is<T>>
    : all_of<is<T>, not_<>> {};
  template<class T> struct any_of_sfinae_falsy<is<T>, not_<>>
    : all_of<is<T>> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T>, C>
    : all_of<is<T>, not_<C>> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T>, not_<C>>
    : all_of<is<T>, C> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T>, not_<not_<C>>>
    : all_of<is<T>, not_<C>> {};

  template<class T> struct all_of_sfinae_falsy<is<T>>
    : none_of<is<T>> {};
  template<class T> struct all_of_sfinae_falsy<is<T>, not_<>>
    : none_of<is<T>, not_<>> {};
  template<class T, class C> struct all_of_sfinae_falsy<is<T>, C>
    : none_of<is<T>, C> {};
  template<class T, class C> struct all_of_sfinae_falsy<is<T>, not_<C>>
    : none_of<is<T>, not_<C>> {};

  /*
   * Pred = is<T, not_<C>>
   */

  template<class T> struct any_of_sfinae_truthy<is<T, not_<>>>
    : all_of<is<T>, not_<>> {};
  template<class T> struct any_of_sfinae_truthy<is<T, not_<>>, not_<>>
    : all_of<is<T>> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T, not_<>>, C>
    : all_of<is<T>, not_<C>> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T, not_<>>, not_<C>>
    : all_of<is<T>, C> {};
  template<class T, class C> struct any_of_sfinae_truthy<is<T, not_<>>, not_<not_<C>>>
    : all_of<is<T>, not_<C>> {};

  template<class T> struct all_of_sfinae_truthy<is<T, not_<>>>
    : none_of<is<T>> {};
  template<class T> struct all_of_sfinae_truthy<is<T, not_<>>, not_<>>
    : none_of<is<T>, not_<>> {};
  template<class T, class C> struct all_of_sfinae_truthy<is<T, not_<>>, C>
    : none_of<is<T>, C> {};
  template<class T, class C> struct all_of_sfinae_truthy<is<T, not_<>>, not_<C>>
    : none_of<is<T>, not_<C>> {};

  template<class T> struct any_of_sfinae_falsy<is<T, not_<>>>
    : none_of<is<T>, not_<>> {};
  template<class T> struct any_of_sfinae_falsy<is<T, not_<>>, not_<>>
    : none_of<is<T>> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T, not_<>>, C>
    : none_of<is<T>, not_<C>> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T, not_<>>, not_<C>>
    : none_of<is<T>, C> {};
  template<class T, class C> struct any_of_sfinae_falsy<is<T, not_<>>, not_<not_<C>>>
    : none_of<is<T>, not_<C>> {};

  template<class T> struct all_of_sfinae_falsy<is<T, not_<>>>
    : all_of<is<T>> {};
  template<class T> struct all_of_sfinae_falsy<is<T, not_<>>, not_<>>
    : all_of<is<T>, not_<>> {};
  template<class T, class C> struct all_of_sfinae_falsy<is<T, not_<>>, C>
    : all_of<is<T>, C> {};
  template<class T, class C> struct all_of_sfinae_falsy<is<T, not_<>>, not_<C>>
    : all_of<is<T>, not_<C>> {};

  /*
   * Pred = is_list<>
   */

#if !JLN_MP_GCC
  template<> struct all_of_sfinae_truthy<is_list<>> : all_of<is_list<>> {};
  template<> struct all_of_sfinae_truthy<is_list<>, not_<>> : all_of<is_list<>, not_<>> {};
  template<class C> struct all_of_sfinae_truthy<is_list<>, C> : all_of<is_list<>, C> {};
  template<class C> struct all_of_sfinae_truthy<is_list<>, not_<C>> : all_of<is_list<>, not_<C>> {};
#endif

  /*
   * If
   */

  template<class Pred, class TC, class FC>
  struct if_<any_of_sfinae_truthy<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      emp::any_of_sfinae_truthy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<any_of_sfinae_truthy<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !emp::any_of_sfinae_truthy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<any_of_sfinae_falsy<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      emp::any_of_sfinae_falsy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<any_of_sfinae_falsy<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !emp::any_of_sfinae_falsy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of_sfinae_truthy<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      emp::all_of_sfinae_truthy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of_sfinae_truthy<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !emp::all_of_sfinae_truthy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of_sfinae_falsy<Pred>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      emp::all_of_sfinae_falsy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };

  template<class Pred, class TC, class FC>
  struct if_<all_of_sfinae_falsy<Pred, not_<>>, TC, FC>
  {
    template<class... xs>
    using f = typename mp::conditional_c<
      !emp::all_of_sfinae_falsy_xs_v<Pred, xs...>
    >::template f<JLN_MP_TRACE_F(TC), JLN_MP_TRACE_F(FC)>
     ::template f<xs...>;
  };
#endif
} // namespace jln::mp
/// \endcond
