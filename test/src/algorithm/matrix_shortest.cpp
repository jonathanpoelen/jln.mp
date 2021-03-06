#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/matrix_shortest.hpp"
#include "jln/mp/smp/list/is_list.hpp"

TEST_SUITE_BEGIN()

template<class...>
struct another_list;

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<seq_0_0, seq_0_1, seq_3_2>,
    emp::matrix_shortest<list<seq_0_0_0, seq_0_1, seq_3_2_1>>
  >();

  test_pack2<matrix_shortest>();

  test_context<matrix_shortest<>, smp::matrix_shortest<>>()
    .test<list<>>()
    .test<list<list<>>, list<>>()
    .test<list<list<>, list<>>, list<>, list<>>()
    .test<list<list<>, list<>>, list<>, seq_0_0_0>()
    .test<list<seq_0>, seq_0>()
    .test<list<seq_0, seq_1>, seq_0, seq_1>()
    .test<list<seq_0_2, seq_1_3>, seq_0_2, seq_1_3>()
    .test<list<seq_0_0, seq_2_1, seq_1_1, seq_0_1>, seq_0_0_0, seq_2_1, seq_1_1_1, seq_0_1_0_2_0_3_0>()
    .not_invocable<int>()
    ;

  test_context<matrix_shortest<is_list<>>, smp::matrix_shortest<smp::is_list<>>>()
    .test<true_, list<>>()
    .not_invocable<>()
    .not_invocable<list<list<>, list<>>, list<>, list<>>()
    .not_invocable<int>()
    ;

  ut::not_invocable<smp::matrix_shortest<bad_function>>();
  ut::not_invocable<smp::matrix_shortest<bad_function>, seq_0_1, seq_0_1>();
  ut::not_invocable<smp::matrix_shortest<bad_function>, seq_0_1, seq_0_1_2_3>();
}

TEST_SUITE_END()
