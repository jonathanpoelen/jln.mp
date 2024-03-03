// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/algorithm/split_at.hpp>
#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/clear.hpp>
#include <jln/mp/utility/is.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    struct before_after_defer_i
    {
      template<class I>
      struct f
      {
        template<class SubC1, class SubC2, class TC, class FC>
        using g = split_at2_with_c<I::value, SubC1, SubC2, TC>;
      };

      struct failure
      {
        template<class...>
        using f = failure;

        template<class SubC1, class SubC2, class TC, class FC>
        using g = FC;
      };
    };
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequences before and after a sub-\sequence.
  /// Calls \c TC with result of \c SubC1 and \c SubC2 called
  /// respectively with the sequences before and after the one found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<
    class Seq,
    class SubC1 = listify, class SubC2 = SubC1,
    class TC = listify, class FC = clear<TC>>
  struct before_after_with
  {};

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;

  template<class... Ts, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<Ts...>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until_xs<sizeof...(xs)>
      ::template f<sizeof...(xs), starts_with<list<Ts...>>, xs...>
    >::template f<
      detail::before_after_defer_i,
      detail::before_after_defer_i::failure,
      sizeof...(xs)
    >
    ::template f<xs...>
    ::template g<SubC1, drop_front_c<sizeof...(Ts), SubC2>, TC, FC>
    ::template f<xs...>;
  };

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after = unpack<L, mp::before_after<Seq, TC, FC>>;

    template<class L, class Seq,
             class SubC1 = mp::listify, class SubC2 = SubC1,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after_with = unpack<L, mp::before_after_with<Seq, SubC1, SubC2, TC, FC>>;
  }

  /// \cond
  template<class T, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<T>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_drop_until<sizeof...(xs)>
      ::template f<0, is<T>, xs...>
    >::template f<
      detail::before_after_defer_i,
      detail::before_after_defer_i::failure,
      sizeof...(xs)
    >
    ::template f<xs...>
    ::template g<SubC1, drop_front_c<1, SubC2>, TC, FC>
    ::template f<xs...>;
  };

  template<class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(TC,
      JLN_MP_DCALL_TRACE_XS_0(xs, SubC1),
      JLN_MP_DCALL_TRACE_XS(xs, SubC2, xs...)
    );
  };
  /// \endcond
}
