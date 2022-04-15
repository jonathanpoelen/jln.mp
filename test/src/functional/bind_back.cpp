#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/bind_back.hpp"
#include "jln/mp/smp/number/numbers.hpp"
#include "jln/mp/smp/list/pop_back.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<bind_back>();

  ut::same<list<char, long, int, void>, emp::bind_back<list<char, long>, listify, int, void>>();

  test_context<
    bind_back<pop_back<>, int, long>,
    smp::bind_back<smp::pop_back<>, int, long>
  >()
    .test<list<int>>()
    .test<list<void, char, int>, void, char>()
    ;

  test_context<
    bind_back_c<listify, 3>,
    smp::bind_back_c<smp::listify, 3>,
    -1
  >()
    .test<seq_3>()
    .test<seq_1_3, _1>()
    ;

#if JLN_MP_ENABLE_TPL_AUTO
  test_context<
    bind_back_v<listify, 3>,
    smp::bind_back_v<smp::listify, 3>,
    -1
  >()
    .test<list<val<3>>>()
    .test<list<_1, val<3>>, _1>()
    ;
#endif

  ut::not_invocable<smp::bind_back<smp::pop_back<>>>();
}

TEST_SUITE_END()
