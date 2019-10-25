#include "test.hpp"

#include "jln/mp/number/operators.hpp"
#include "jln/mp/number/numbers.hpp"

TEST_SUITE_BEGIN()

struct bad_number
{
  class a {};
  constexpr static a value {};
};

TEST()
{
  using namespace jln::mp;

  using e = list<>;
  using l0 = emp::numbers<0, 0, 0>;
  using l1 = emp::numbers<1, 1, 1>;
  using _42 = emp::numbers<42>;
  using seq_0_1_2 = emp::numbers<0, 1, 2>;
  using seq_1_2_3 = emp::numbers<1, 2, 3>;
  using seq_2_1_0 = emp::numbers<2, 1, 0>;
  using seq_3_2_1 = emp::numbers<3, 2, 1>;
  using bad_seq1 = list<bad_number>;
  using bad_seq2 = list<bad_number, bad_number>;

  emp::and_<e>() = true_();
  emp::or_<e>() = false_();
  emp::or_<l1>() = true_();
  emp::or_<l0>() = false_();

  test_pack<or_>()
    .test_unary()
  ;

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, sfinae<g>>();
  };

  ctx(or_())
    .test<false_, e>()
    .test<false_, l0>()
    .test<true_, l1>()
    .not_invocable<bad_seq1>()
    .not_invocable<bad_seq2>()
    ;

  ctx(and_())
    .test<true_, e>()
    .test<false_, l0>()
    .test<true_, l1>()
    ;

  ctx(div())
    .test<number<42>, _42>()
    .test<number<1>, l1>()
    .test<number<0>, seq_0_1_2>()
    .test<number<0>, seq_1_2_3>()
    .test<number<1>, seq_3_2_1>()
    .not_invocable<e>()
    .not_invocable<seq_2_1_0>()
    .not_invocable<l0>()
    ;

  using _0 = number<0>;
  using _1 = number<1>;
  using _3 = number<3>;

  ctx(add0<>())
    .test<_0, e>()
    .test<_0, l0>()
    .test<_3, l1>()
    ;

  using _0 = number<0>;
  using _1 = number<1>;

  INVOKE_IS_SAME(_0, div0<>);
  INVOKE_IS_SAME(_1, div0<>, _1);
  INVOKE_IS_SAME(_0, smp::div0<>);
  INVOKE_IS_SAME(_1, smp::div1<>);
  INVOKE_IS_SAME(_0, smp::div0<>, _0);
  INVOKE_IS_SAME(_1, smp::div0<>, _1);
  not IS_INVOCABLE(smp::div0<>, _1, _0);

  test_context<not_<>, smp::not_<>>()
    .test<_1, _0>()
    .test<_0, _1>()
    .not_invocable<e>()
    ;
}

TEST_SUITE_END()
