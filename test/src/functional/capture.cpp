#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/capture.hpp"
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

  test_pack2<capture>();

  test_context<capture<int, char>, smp::capture<int, char>>()
    .test<list<char>, pop_front<>>()
    .test<list<>, pop_front<pop_front<>>>()
    .not_invocable<void>()
    .not_invocable<pop_front<pop_front<pop_front<>>>>()
    .not_invocable<pop_front<pop_front<smp::pop_front<>>>>()
    ;

  test_context<capture_v<void>, smp::capture_v<void>>()
    .not_invocable<listify>()
    ;

  test_context<capture_v<_1, _2>, smp::capture_v<_1, _2>>()
    .test<foo::f<1, 2>, foo>()
    .not_invocable<listify>()
    ;

  test_context<capture_c<1, 2>, smp::capture_c<1, 2>>()
    .not_invocable<listify>()
    ;
}

TEST_SUITE_END()
