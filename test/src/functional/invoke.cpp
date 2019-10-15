#include "test.hpp"
#include "test/is_same.hpp"

#include "jln/mp/functional/invoke.hpp"
#include "jln/mp/list/join.hpp"

namespace
{
  using namespace jln::mp;

  IGNORE_UNUSED_FUNCTION_PUSH()

  template<class T, class... Ts>
  invoke<join<>, T, Ts...> invoke1(T*, Ts*...);

  void invoke1(...);

  template<class T, class... Ts>
  invoke<join<join<>>, T, Ts...> invoke2(T*, Ts*...);

  void invoke2(...);

  TEST()
  {
    using l1 = int*;
    using l2 = list<>*;
    using l3 = list<int>*;
    using l4 = list<list<>>*;
    using l5 = list<list<>, list<>>*;
    using l6 = list<list<int>>*;

    IS_SAME_V(invoke1(l1()), void);
    IS_SAME_V(invoke1(l2()), list<>);
    IS_SAME_V(invoke1(l3()), list<int>);
    IS_SAME_V(invoke1(l3(), l3()), list<int, int>);
    IS_SAME_V(invoke1(l4()), list<list<>>);

    IS_SAME_V(invoke2(char()), void);
    IS_SAME_V(invoke2(l1()), void);
    IS_SAME_V(invoke2(l2()), list<>);
    IS_SAME_V(invoke2(l2(), l2()), list<>);
    IS_SAME_V(invoke2(l3()), void);
    IS_SAME_V(invoke2(l4()), list<>);
    IS_SAME_V(invoke2(l5()), list<>);
    IS_SAME_V(invoke2(l6()), list<int>);
    IS_SAME_V(invoke2(l6(), l6()), list<int, int>);
  }
}
