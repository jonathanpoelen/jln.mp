#include "test.hpp"

#include "jln/mp/smp/utility/is_instance_of.hpp"
#include "jln/mp/list/size.hpp"
#include "jln/mp/list/list.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::is_instance_of<list, list<>>>();
  ut::same<true_, emp::is_instance_of<list, list<int, int>>>();
  ut::same<false_, emp::is_instance_of<size, list<int, int>>>();

  test_context<is_instance_of<list>, smp::is_instance_of<list>>()
    .test<true_, list<>>()
    .test<true_, list<int, int>>()
    .test<false_, size<>>()
    .test<false_, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<is_instance_of<size>, smp::is_instance_of<size>>()
    .test<false_, list<>>()
    .test<false_, list<int, int>>()
    .test<true_, size<>>()
    .test<false_, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::is_instance_of<size, bad_function>>();
  ut::not_invocable<smp::is_instance_of<size, bad_function>, size<>>();
}

TEST_SUITE_END()
