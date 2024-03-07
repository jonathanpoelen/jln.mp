// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/list/listify.hpp>

namespace jln::mp
{
  namespace detail
  {
    template<class C>
    struct continuation_fn_impl
    {
      template<class... Ts>
      static typename C::template f<Ts...> impl(list<Ts...>*);
    };

    template<class C, class... Ts>
    struct remove_prefix_impl
    {
      template<class... Us>
      static typename C::template f<Us...> impl(list<Ts..., Us...>*);
    };
  }

  /// \ingroup algorithm

  /// Remove the first elements corresponding to a prefix.
  /// Calls \c TC with the rest of sequence when the prefix is found,
  /// otherwise calls \c FC with the whole \sequence.
  /// \treturn \sequence
  /// \see remove_suffix, starts_with, ends_with
  template<class Seq, class TC = listify, class FC = TC>
  struct remove_prefix
  {};

  template<class... Ts, class TC, class FC>
  struct remove_prefix<list<Ts...>, TC, FC>
      : detail::continuation_fn_impl<FC>
      , detail::remove_prefix_impl<TC, Ts...>
  {
    using detail::continuation_fn_impl<FC>::impl;
    using detail::remove_prefix_impl<TC, Ts...>::impl;

    template<class... xs>
    using f = decltype(impl(static_cast<list<xs...>*>(nullptr)));
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = TC>
    using remove_prefix = unpack<L, remove_prefix<Seq, TC, FC>>;
  }

  /// \cond
  template<class TC, class FC>
  struct remove_prefix<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_FORCE_DCALL_TRACE_XS(xs, TC, xs...);
  };

  template<class FC>
  struct remove_prefix<list<>, listify, FC>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
}
