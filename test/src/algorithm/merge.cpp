#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/merge.hpp"

TEST_SUITE_BEGIN()

template<class tag>
struct sized_type
{
  int d;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_binary_pack<merge>();
  test_mulary_pack<merge, listify>();

  ut::same<list<_0, _1, _1, _2, _2, _3>, emp::merge<list<seq_0_1_2, seq_1_2_3>>>();

  // check stable sort
  ut::same<list<int, char[4], int>, merge<always<false_>>::f<list<int, char[4]>, list<int>>>();

  ut::same<list<
    sized_type<_1>, sized_type<_2>, sized_type<_3>, sized_type<_4>,
    sized_type<_5>, sized_type<_6>, sized_type<_7>, sized_type<_8>,
    sized_type<_9>, sized_type<_10>, sized_type<_11>, sized_type<_12>,
    sized_type<_13>, sized_type<_14>, sized_type<_15>, sized_type<_16>,
    sized_type<_17>, sized_type<_18>, sized_type<_19>, sized_type<_20>
  >, merge<always<false_>>::f<
    list<
      sized_type<_1>, sized_type<_2>, sized_type<_3>, sized_type<_4>,
      sized_type<_5>, sized_type<_6>, sized_type<_7>, sized_type<_8>,
      sized_type<_9>, sized_type<_10>
    >,
    list<
      sized_type<_11>, sized_type<_12>, sized_type<_13>, sized_type<_14>,
      sized_type<_15>, sized_type<_16>, sized_type<_17>, sized_type<_18>,
      sized_type<_19>, sized_type<_20>
    >
  >>();

  test_context<merge<>, smp::merge<>>()
    .test<list<>, list<>, list<>>()
    .test<list<_0, _1>, list<_0>, list<_1>>()
    .test<list<_0, _1>, list<>, list<_0, _1>>()
    .test<list<_0, _1>, list<_0, _1>, list<>>()
    .test<list<bad_number>, list<>, list<bad_number>>()
    .not_invocable<list<>, int>()
    .not_invocable<list<bad_number>, list<bad_number>>()
    ;

  ut::not_invocable<smp::merge<smp::always<na>>, _1, _1>();
  ut::not_invocable<smp::merge<bad_function>, _1, _1>();
  ut::not_invocable<smp::merge<always<void>>, _1, _1>();
  ut::not_invocable<smp::merge<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::merge<always<true_>, bad_function>, _1, _1>();
}

TEST_SUITE_END()
