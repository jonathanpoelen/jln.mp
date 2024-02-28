// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/ends_with.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Remove the last elements corresponding to a suffix.
  /// Calls \c TC with the rest of sequence when the suffix is found,
  /// otherwise calls \c FC with the whole \sequence.
  /// \treturn \sequence
  /// \see remove_prefix, starts_with, ends_with
  template<class Seq, class TC = listify, class FC = TC>
  struct remove_suffix
  {};

  template<class... Ts, class TC, class FC>
  struct remove_suffix<list<Ts...>, TC, FC>
  {
    template<class... xs>
    using f = typename conditional_c<
      detail::ends_with_impl<sizeof...(Ts) <= sizeof...(xs)>
      ::template f<sizeof...(Ts), list<Ts...>, xs...>
      ::value
    >
      ::template f<take_front_c<static_cast<unsigned>(sizeof...(xs) - sizeof...(Ts)), TC>, FC>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = TC>
    using remove_suffix = unpack<remove_suffix<Seq, TC, FC>, L>;
  }

  /// \cond
  template<class TC, class FC>
  struct remove_suffix<list<>, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_FORCE_DCALL_TRACE_XS(xs, TC, xs...);
  };

  template<class FC>
  struct remove_suffix<list<>, listify, FC>
  {
    template<class... xs>
    using f = list<xs...>;
  };
  /// \endcond
}
