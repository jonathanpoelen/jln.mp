#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/value/operators.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;

  using yes = val<true>;
  using no = val<false>;

  ut::same<yes, emp::and_seq_v<e>>();
  ut::same<no, emp::or_seq_v<e>>();
  ut::same<yes, emp::or_seq_v<seq_1_1_1>>();
  ut::same<no, emp::or_seq_v<seq_0_0_0>>();

  ut::same<yes, emp::or_v<_0, _1, _0>>();
  ut::same<no, emp::or_v<>>();
  ut::same<no, emp::and_v<_0, _1, _0>>();
  ut::same<yes, emp::and_v<>>();

  ut::same<no, emp::not_v<yes>>();

  ut::same<yes, emp::or_c_v<0, 1, 0>>();
  ut::same<no, emp::or_c_v<>>();
  ut::same<no, emp::and_c_v<0, 1, 0>>();
  ut::same<yes, emp::and_c_v<>>();


  test_pack<or_v>().test_unary();
  test_pack3<or_v>();

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, detail::sfinae<g>>();
  };

  ctx(or_v<>())
    .test<no, e>()
    .test<no, seq_0_0_0>()
    .test<yes, seq_1_1_1>()
    .not_invocable<seq_bad>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(and_v<>())
    .test<yes, e>()
    .test<no, seq_0_0_0>()
    .test<yes, seq_1_1_1>()
    ;

  ctx(div_v<>())
    .test<val<int_(42)>, list<_42>>()
    .test<val<int_(1)>, seq_1_1_1>()
    .test<val<int_(0)>, seq_0_1_2>()
    .test<val<int_(0)>, seq_1_2_3>()
    .test<val<int_(1)>, seq_3_2_1>()
    .not_invocable<e>()
    .not_invocable<seq_2_1_0>()
    .not_invocable<seq_0_0_0>()
    ;

  ctx(add0_v<>())
    .test<val<0>, e>()
    .test<val<int_(0)>, seq_0_0_0>()
    .test<val<int_(3)>, seq_1_1_1>()
    ;

  ut::invoke_r<val<0>, div0_v<>>();
  ut::invoke_r<val<int_(1)>, div0_v<>, _1>();
  // FIX gcc7: val<0> is a typed_val<int_,0> if val<int_(0)> precedes val<0>
  if constexpr (std::is_same_v<val<0>, typed_val<int,0>>) {
    ut::invoke_r<val<0>, smp::div0_v<>>();
    ut::invoke_r<val<1>, smp::div1_v<>>();
  }
  ut::invoke_r<val<int_(0)>, smp::div0_v<>, _0>();
  ut::invoke_r<val<int_(1)>, smp::div0_v<>, _1>();
  ut::not_invocable<smp::div0_v<>, _1, _0>();
  ut::invoke_r<val<1>, smp::div0_v<inc_v<>>>();
  ut::invoke_r<val<2>, smp::div1_v<inc_v<>>>();

  ut::invoke_r<val<true>, smp::equal_than_v<_3>, _3>();
  ut::invoke_r<val<false>, smp::not_equal_than_v<_3>, _3>();
  ut::invoke_r<val<true>, smp::less_than_v<_3>, _2>();
  ut::invoke_r<val<true>, smp::less_equal_than_v<_3>, _3>();
  ut::invoke_r<val<true>, smp::greater_than_v<_1>, _3>();
  ut::invoke_r<val<true>, smp::greater_equal_than_v<_3>, _3>();

  test_context<not_v<>, smp::not_v<>>()
    .test<val<true>, _0>()
    .test<val<false>, _1>()
    .not_invocable<e>()
    ;

  ut::not_invocable<smp::not_v<bad_function>>();
  ut::not_invocable<smp::not_v<bad_function>, no>();
  ut::not_invocable<smp::div0_v<bad_function>>();
  ut::not_invocable<smp::div0_v<bad_function>, _1, _1>();
}

TEST_SUITE_END()
