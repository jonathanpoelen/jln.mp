// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/drop_until.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Checks whether a predicate does not hold for any element of a \sequence.
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

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = unpack<L, mp::none_of<Pred, C>>;

    template<class Pred, class... xs>
    using none_of_xs = typename mp::none_of<Pred>::template f<xs...>;

    template<class L, class Pred, class C = mp::identity>
    inline constexpr bool none_of_v = unpack<L, mp::none_of<Pred, C>>::value;

    template<class Pred, class... xs>
    inline constexpr bool none_of_xs_v = mp::none_of<Pred>::template f<xs...>::value;
  }
} // namespace jln::mp

#include <jln/mp/number/not.hpp>
#include <jln/mp/functional/if.hpp>

/// \cond
namespace jln::mp
{
  template<class Pred>
  struct none_of<Pred, identity>
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
} // namespace jln::mp
/// \endcond
