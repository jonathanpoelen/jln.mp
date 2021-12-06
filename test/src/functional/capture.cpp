#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/capture.hpp"
#include "jln/mp/smp/functional/identity.hpp"
#include "jln/mp/smp/list/pop_front.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<int...>
  struct f {};
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_context<capture<int, char>, smp::capture<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .test<list<int, char, void>, listify, void>()
    .not_invocable<smp::identity>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<capture_v<void>, smp::capture_v<void>>()
    .not_invocable<listify, int>()
    .not_invocable<listify, _2>()
    .not_invocable<listify>()
    ;

  test_context<capture_v<_1, _2>, smp::capture_v<_1, _2>>()
    .test<foo::f<1, 2>, foo>()
    .test<foo::f<1, 2, 3>, foo, _3>()
    .not_invocable<listify>()
    ;

  test_context<reverse_capture<int, char>, smp::reverse_capture<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .test<list<void, int, char>, listify, void>()
    .not_invocable<smp::identity>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<reverse_capture_v<void>, smp::reverse_capture_v<void>>()
    .not_invocable<listify, int>()
    .not_invocable<listify, _2>()
    .not_invocable<listify>()
    ;

  test_context<reverse_capture_v<_1, _2>, smp::reverse_capture_v<_1, _2>>()
    .test<foo::f<1, 2>, foo>()
    .test<foo::f<3, 1, 2>, foo, _3>()
    .not_invocable<listify>()
    ;

  test_context<reverse_capture_v_c<1, 2>, smp::reverse_capture_v_c<1, 2>>()
    .test<foo::f<1, 2>, foo>()
    .not_invocable<listify>()
    ;
}

TEST_SUITE_END()
