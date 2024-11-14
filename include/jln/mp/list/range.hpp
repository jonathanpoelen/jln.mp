// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/list/list.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ beg, int_ end,
      bool = beg < 0,
      bool = end < 0,
      bool = beg >= end>
    struct _range;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a contiguous subsequence of a \sequence.
  /// A negative value represents an index starting from the end.
  /// All indices available in the range are returned, indices outside the bounds are ignored.
  /// \treturn \sequence
  template<int_ beg, int_ end, class C = listify>
  struct range_c : detail::_range<beg, end>::template impl<C>
  {
#ifdef JLN_MP_DOXYGENATING
    template<class... xs>
    using f;
#endif
  };

  template<class beg, class end, class C = listify>
  using range = range_c<beg::value, end::value, C>;

  namespace emp
  {
    template<class L, class beg, class end, class C = mp::listify>
    using range = typename detail::_unpack<mp::range<beg, end, C>, L>::type;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = typename detail::_unpack<mp::range_c<beg, end, C>, L>::type;
  }
}


#include <jln/mp/list/slice.hpp>

/// \cond
namespace jln::mp::detail
{
  // beg < 0 && end < 0 && beg >= end
  template<int_ beg, int_ end>
  struct _range<beg, end, true, true, true>
    : positive_strided_slice_impl<-1, -1>
  {};

  // beg < 0 && end < 0 && beg < end
  template<int_ beg, int_ end>
  struct _range<beg, end, true, true, false>
  {
    template<class C>
    using impl = negative_slice_select<true>::impl<beg, end - beg, C>;
  };

  // pre: beg >= 0
  // pre: end < 0
  template<class C, int_ beg, int_ end, int_ n,
    bool b = n + end <= beg>
  using negative_end_range_dispatch = slice_impl<
    C,
    b ? -1 : beg,
    b ? -1 : -end
  >;

  // beg >= 0 && end < 0
  template<int_ beg, int_ end>
  struct _range<beg, end, false, true, true>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_end_range_dispatch<C, beg, end,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  // pre: beg < 0
  // pre: end >= 0
  template<class C, int_ beg, int_ end, int_ n,
    bool b = end <= n + beg>
  using negative_beg_range_dispatch = slice_impl<
    C,
    b ? -1 : n < -beg ? 0 : n + beg,
    b ? -1 : n < end ? 0 : n - end
  >;

  // beg < 0 && end >= 0
  template<int_ beg, int_ end>
  struct _range<beg, end, true, false, false>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename negative_beg_range_dispatch<C, beg, end,
        static_cast<int_>(sizeof...(xs)) // cast is necessary for nvcc (tested with V12.3.52)
      >::template f<xs...>;
    };
  };

  // beg >= 0 && end >= 0 && beg < end
  template<int_ beg, int_ end>
  struct _range<beg, end, false, false, false>
  {
    template<class C>
    using impl = negative_slice_select<false>::impl<beg, end - beg, C>;
  };

  // beg >= 0 && end >= 0 && beg >= end
  template<int_ beg, int_ end>
  struct _range<beg, end, false, false, true>
    : positive_strided_slice_impl<-1, -1>
  {};
}
/// \endcond
