#include "jln/mp/list/join.hpp"
#include <boost/mp11/algorithm.hpp>

using jln::mp::list;

namespace detail
{
  template<class>
  struct _distinct;
};

template<class C = jln::mp::listify>
struct distinct
{
  template<class... xs>
  using f = typename jln::mp::join<C>::template f<
    typename detail::_distinct<list<xs...>>::template f<xs>...>;
};

namespace detail
{
  template<class seq, class x>
  struct _distinct_tag
  {
    friend constexpr auto _distinct_test(_distinct_tag<seq, x>);
  };

  template<class seq, class x, bool y>
  struct _distinct_impl
  {
    friend constexpr auto _distinct_test(_distinct_tag<seq, x>)
    {
      return 1;
    }

    using type = list<x>;
  };

  template<class seq, class x>
  struct _distinct_impl<seq, x, true>
  {
    using type = list<>;
  };

  template<class seq>
  struct _distinct
  {
    template<class x> static long long test(...);
    template<class x, int = sizeof(_distinct_test(_distinct_tag<seq, x>()))> static bool test(int);

    template<class x, bool v = sizeof(bool) == sizeof(test<x>(0))>
    using f = typename _distinct_impl<seq, x, v>::type;
  };
};

