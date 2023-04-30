#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/rewrap_unpack.hpp"
#include "jln/mp/smp/list/push_back.hpp"

TEST_SUITE_BEGIN()

template<class... xs>
struct my_list
{};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<rewrap_unpack>();
  test_mulary_pack<rewrap_unpack_append>();

  ut::same<list<_0, _0, int>, emp::rewrap_unpack<seq_0_0, push_back<int>>>();
  ut::same<list<char, _0, _0, int>, emp::rewrap_unpack<seq_0_0, push_back<int>, char>>();
  ut::same<list<_0, _0, int>, emp::rewrap_unpack_append<seq_0_0, push_back<int>>>();
  ut::same<list<_0, _0, char, int>, emp::rewrap_unpack_append<seq_0_0, push_back<int>, char>>();

  test_context<rewrap_unpack<push_back<int>>, smp::rewrap_unpack<smp::push_back<int>>>()
    .test<list<int>, list<>>()
    .test<list<_0, _1, int>, list<>, _0, _1>()
    .test<list<_0, _1, _2, int>, list<_2>, _0, _1>()
    .test<my_list<int>, my_list<>>()
    .test<my_list<_0, _1, int>, my_list<>, _0, _1>()
    .test<my_list<_0, _1, _2, int>, my_list<_2>, _0, _1>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<rewrap_unpack_append<push_back<int>>, smp::rewrap_unpack_append<smp::push_back<int>>>()
    .test<list<int>, list<>>()
    .test<list<_0, _1, int>, list<>, _0, _1>()
    .test<list<_2, _0, _1, int>, list<_2>, _0, _1>()
    .test<my_list<int>, my_list<>>()
    .test<my_list<_0, _1, int>, my_list<>, _0, _1>()
    .test<my_list<_2, _0, _1, int>, my_list<_2>, _0, _1>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;


  ut::not_invocable<smp::rewrap_unpack<bad_function>>();
  ut::not_invocable<smp::rewrap_unpack<bad_function>, list<>>();
  ut::not_invocable<smp::rewrap_unpack_append<bad_function>>();
  ut::not_invocable<smp::rewrap_unpack_append<bad_function>, list<>>();
}

TEST_SUITE_END()
