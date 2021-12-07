#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/take_front.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<unsigned position, class C1, class C2, class C, class... xs>
    using _split_by_i = typename C::template f<
      typename take_front_c<position, C1>::template f<xs...>,
      typename drop_front_c<position, C2>::template f<xs...>
    >;
  }
  /// \endcond

  /// \ingroup group

  /// Splits a sequence at an arbitrary position returns by \c GetIndex.
  /// \pre `GetIndex::f<xs...>::value >= 0 && GetIndex::f<xs...>::value <= sizeof...(xs)`
  /// \treturn \sequence of two \values
  template<class GetIndex, class SubC1 = listify, class SubC2 = SubC1, class C = listify>
  struct split_by
  {
    template<class... xs>
    using f = typename detail::_split_by_i<
      JLN_MP_DCALL_V_TRACE_XS(xs, GetIndex, xs...), SubC1, SubC2, C, xs...>;
  };

  template<class GetIndex, class C = listify>
  using split_by2 = split_by<GetIndex, listify, listify, C>;

  namespace emp
  {
    template<class L, class GetIndex,
      class SubC1 = mp::listify, class SubC2 = SubC1, class C = mp::listify>
    using split_by = unpack<L, mp::split_by<GetIndex, SubC1, SubC2, C>>;

    template<class L, class GetIndex, class C = mp::listify>
    using split_by2 = unpack<L, mp::split_by<GetIndex, mp::listify, mp::listify, C>>;
  }
}
