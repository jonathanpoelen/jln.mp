#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/arrange.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<arrange, int_seq_v<>>();

  using Ints = emp::numbers<2, 4, 0, 4>;

  ut::same<list<char, int, void, int>,
    emp::arrange<list<void, _1, char, _3, int, _5>, Ints>>();

  ut::same<list<>, emp::arrange<seq_0_1_2_3, list<>>>();

  test_context<arrange<Ints>, smp::arrange<Ints>>()
    .test<list<char, int, void, int>, void, _1, char, _3, int, _5>()
    .not_invocable<>()
    .not_invocable<_0>()
    .not_invocable<_0, _1, _2, _3>()
    ;

  ut::not_invocable<smp::arrange<void>, _1>();
  ut::not_invocable<smp::arrange<Ints, bad_function>, _1>();
}

TEST_SUITE_END()
