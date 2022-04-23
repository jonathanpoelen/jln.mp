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
      bool = end < 0 || beg == -1,
      bool = beg >= end || beg == -1>
    struct _range;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a contiguous subsequence of a \sequence.
  /// A negative value represents an index starting from the end + 1.
  /// if finally, \c end <= \c beg, then an empty \list is returned.
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
    using range = unpack<L, mp::range<beg, end, C>>;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = unpack<L, mp::range_c<beg, end, C>>;
  }
}

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/algorithm/rotate.hpp>
#include <jln/mp/detail/compiler.hpp>

/// \cond
namespace jln::mp::detail
{
  template<bool, bool>
  struct range_impl
  {
    template<class C, int_ beg, int_ end, int_ n>
    using f = clear<C>;
  };

  template<>
  struct range_impl<true, true>
  {
    template<class C, int_ beg, int_ end, int_ n>
    using f = rotate_c<end, drop_front_c<n - end + beg, C>>;
  };

  template<>
  struct range_impl<true, false>
  {
    template<class C, int_ beg, int_ end, int_ n>
    using f = drop_front_c<beg, C>;
  };

  template<class C, int_ beg, int_ end, int_ n>
  using range_select = typename range_impl<beg < n, end < n>
    ::template f<C, beg, end, n>;

  template<>
  struct _range<0, -1, false, true, false>
  {
    template<class C>
    using impl = C;
  };

  // end >= 0 && beg >= end
  template<int_ beg, int_ end>
  struct _range<beg, end, false, false, true>
  {
    template<class C>
    using impl = clear<C>;
  };

  // end < 0 && beg < 0 && beg >= end
  // or
  // beg = -1
  template<int_ beg, int_ end>
  struct _range<beg, end, true, true, true>
  {
    template<class C>
    using impl = clear<C>;
  };

  // beg < 0 and end < 0
  template<int_ beg, int_ end, bool b3>
  struct _range<beg, end, true, true, b3>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename range_select<C,
        sizeof...(xs) <= -beg ? 0 : int_(sizeof...(xs)) + beg,
        sizeof...(xs) <= -end ? 0 : int_(sizeof...(xs)) + end + 1,
        sizeof...(xs)
      >::template f<xs...>;
    };
  };

  // beg >= 0 and end < 0
  template<int_ beg, int_ end, bool b3>
  struct _range<beg, end, false, true, b3>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename range_select<C,
        beg,
        sizeof...(xs) <= -end ? 0 : int_(sizeof...(xs)) + end + 1,
        sizeof...(xs)
      >::template f<xs...>;
    };
  };

  // beg < 0 and end >= 0
  template<int_ beg, int_ end, bool b3>
  struct _range<beg, end, true, false, b3>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
      using f = typename range_select<C,
        sizeof...(xs) <= -beg ? 0 : int_(sizeof...(xs)) + beg,
        end,
        sizeof...(xs)
      >::template f<xs...>;
    };
  };

  // beg >= 0 and end >= 0
  template<int_ beg, int_ end, bool b3>
  struct _range<beg, end, false, false, b3>
  {
    template<class C>
    struct impl
    {
      template<class... xs>
#if JLN_MP_GCC
      using f = typename range_select<C, beg, end, sizeof...(xs)>
#else
      using f = typename range_impl<beg < sizeof...(xs), end < sizeof...(xs)>
        ::template f<C, beg, end, sizeof...(xs)>
#endif
        ::template f<xs...>;
    };
  };
}
/// \endcond
