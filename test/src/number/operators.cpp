#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;

  ut::same<true_, emp::and_seq<e>>();
  ut::same<false_, emp::or_seq<e>>();
  ut::same<true_, emp::or_seq<seq_1_1_1>>();
  ut::same<false_, emp::or_seq<seq_0_0_0>>();

  ut::same<true_, emp::or_<_0, _1, _0>>();
  ut::same<false_, emp::or_<>>();
  ut::same<false_, emp::and_<_0, _1, _0>>();
  ut::same<true_, emp::and_<>>();

  ut::same<false_, emp::not_<true_>>();

  ut::same<true_, emp::or_c<0, 1, 0>>();
  ut::same<false_, emp::or_c<>>();
  ut::same<false_, emp::and_c<0, 1, 0>>();
  ut::same<true_, emp::and_c<>>();


  test_unary_pack<or_>();

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, detail::sfinae<g>>();
  };

  ctx(or_<>())
    .test<false_, e>()
    .test<false_, seq_0_0_0>()
    .test<true_, seq_1_1_1>()
    .not_invocable<seq_bad>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(and_<>())
    .test<true_, e>()
    .test<false_, seq_0_0_0>()
    .test<true_, seq_1_1_1>()
    ;

  ctx(div<>())
    .test<_42, list<_42>>()
    .test<_1, seq_1_1_1>()
    .test<_0, seq_0_1_2>()
    .test<_0, seq_1_2_3>()
    .test<_1, seq_3_2_1>()
    .not_invocable<e>()
    .not_invocable<seq_2_1_0>()
    .not_invocable<seq_0_0_0>()
    ;

  ctx(add0<>())
    .test<_0, e>()
    .test<_0, seq_0_0_0>()
    .test<_3, seq_1_1_1>()
    ;

  ut::invoke_r<_0, div0<>>();
  ut::invoke_r<_1, div0<>, _1>();
  ut::invoke_r<_0, smp::div0<>>();
  ut::invoke_r<_1, smp::div1<>>();
  ut::invoke_r<_0, smp::div0<>, _0>();
  ut::invoke_r<_1, smp::div0<>, _1>();
  ut::invoke_r<_2, smp::div0<>, _2>();
  ut::not_invocable<smp::div0<>, _1, _0>();
  ut::invoke_r<_1, smp::div0<inc<>>>();
  ut::invoke_r<_2, smp::div1<inc<>>>();

  ut::invoke_r<_1, smp::equal_to<_3>, _3>();
  ut::invoke_r<_0, smp::not_equal_to<_3>, _3>();
  ut::invoke_r<_1, smp::less_than<_3>, _2>();
  ut::invoke_r<_1, smp::less_equal_than<_3>, _3>();
  ut::invoke_r<_1, smp::greater_than<_1>, _3>();
  ut::invoke_r<_1, smp::greater_equal_than<_3>, _3>();

  test_context<not_<>, smp::not_<>>()
    .test<_1, _0>()
    .test<_0, _1>()
    .not_invocable<e>()
    ;

  ut::not_invocable<smp::not_<bad_function>>();
  ut::not_invocable<smp::not_<bad_function>, false_>();
  ut::not_invocable<smp::div0<bad_function>>();
  ut::not_invocable<smp::div0<bad_function>, _1, _1>();
}

TEST_SUITE_END()
