#pragma once

#include "reverse.hpp"
#include "../list/take.hpp"
#include "../list/drop.hpp"
#include "../list/push_front.hpp"
#include "../functional/fork.hpp"
#include "../functional/fork_front.hpp"
#include "../functional/call.hpp"
#include "../number/operators.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<int_ beg, int_ end, class C, bool _
      = !(beg == -1
      || ((beg >= 0 ? end >= 0 : end < 0) && beg >= end)),
      bool = _ && (beg >= 0),
      bool = _ && (end >= 0)>
    struct _range;
  }

  template<class beg, class end, class C = listify>
  struct range : detail::_range<beg::value, end::value, C>::type
  {
    // TODO doc
    // template<class... xs>
    // using f;
  };

  template<int_ beg, int_ end, class C = listify>
  using range_c = typename detail::_range<beg, end, C>::type;

  namespace emp
  {
    template<class L, class beg, class end, class C = mp::listify>
    using range = eager<L, mp::range<beg, end, C>>;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = eager<L, mp::range_c<beg, end, C>>;
  }
}

namespace jln::mp::detail
{
  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, false, false, false>
  {
    using type = always<C, cfe<call>>;
  };

  template<int_ beg, int_ end>
  struct _range<beg, end, listify, false, false, false>
  {
    using type = always<list<>>;
  };

  template<class C>
  struct _range<0, -1, C, true, true, false>
  {
    using type = C;
  };

  template<int_ beg, int_ end, class C, bool b1, bool b2>
  struct _range<beg, end, C, true, b1, b2>
  {
    struct impl
    {
      template<class... xs>
      using f = typename range_c<
        (beg >= 0
          ? beg
          : (sizeof...(xs) <= -beg
            ? 0
            : int_(sizeof...(xs)) + beg)),
        (end >= 0
          ? end
          : (sizeof...(xs) <= -end
            ? 0
            : int_(sizeof...(xs)) + (end+1))),
        C
      >::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, int_ end, int_ n, class C,
    bool = (beg < n), bool = (end < n)>
  struct _range_impl // true, true
  {
    using type = drop_c<beg, take_c<end - beg, C>>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, true>
  {
    using type = take_c<end, C>;
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, true, false>
  {
    using type = drop_c<beg, C>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, false>
  {
    using type = C;
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, false, false>
  {
    using type = always<C, cfe<call>>;
  };

  template<int_ beg, int_ end, int_ n>
  struct _range_impl<beg, end, n, listify, false, false>
  {
    using type = always<list<>>;
  };

  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, true, true, true>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, end, sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, class C>
  struct _range<beg, -1, C, true, true, false>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, sizeof...(xs), sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };
}