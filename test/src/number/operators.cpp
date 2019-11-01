#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  using e = list<>;

  IS_SAME(true_, emp::and_seq<e>);
  IS_SAME(false_, emp::or_seq<e>);
  IS_SAME(true_, emp::or_seq<seq_1_1_1>);
  IS_SAME(false_, emp::or_seq<seq_0_0_0>);

  IS_SAME(true_, emp::or_<_0, _1, _0>);
  IS_SAME(false_, emp::or_<>);
  IS_SAME(false_, emp::and_<_0, _1, _0>);
  IS_SAME(true_, emp::and_<>);

  IS_SAME(false_, emp::not_<true_>);

  IS_SAME(true_, emp::or_c<0, 1, 0>);
  IS_SAME(false_, emp::or_c<>);
  IS_SAME(false_, emp::and_c<0, 1, 0>);
  IS_SAME(true_, emp::and_c<>);


  test_pack<or_>()
    .test_unary()
  ;

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, sfinae<g>>();
  };

  ctx(or_())
    .test<false_, e>()
    .test<false_, seq_0_0_0>()
    .test<true_, seq_1_1_1>()
    .not_invocable<seq_bad>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(and_())
    .test<true_, e>()
    .test<false_, seq_0_0_0>()
    .test<true_, seq_1_1_1>()
    ;

  ctx(div())
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

  INVOKE_IS_SAME(_0, div0<>);
  INVOKE_IS_SAME(_1, div0<>, _1);
  INVOKE_IS_SAME(_0, smp::div0<>);
  INVOKE_IS_SAME(_1, smp::div1<>);
  INVOKE_IS_SAME(_0, smp::div0<>, _0);
  INVOKE_IS_SAME(_1, smp::div0<>, _1);
  IS_NOT_INVOCABLE(smp::div0<>, _1, _0);
  INVOKE_IS_SAME(_1, smp::div0<inc<>>);
  INVOKE_IS_SAME(_2, smp::div1<inc<>>);

  INVOKE_IS_SAME(_1, smp::equal_than<_3>, _3);
  INVOKE_IS_SAME(_0, smp::not_equal_than<_3>, _3);
  INVOKE_IS_SAME(_1, smp::less_than<_3>, _2);
  INVOKE_IS_SAME(_1, smp::less_equal_than<_3>, _3);
  INVOKE_IS_SAME(_1, smp::greater_than<_1>, _3);
  INVOKE_IS_SAME(_1, smp::greater_equal_than<_3>, _3);

  test_context<not_<>, smp::not_<>>()
    .test<_1, _0>()
    .test<_0, _1>()
    .not_invocable<e>()
    ;
}

TEST_SUITE_END()
