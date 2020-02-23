#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/number/math.hpp"
#include "jln/mp/smp/number/numbers.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using e = list<>;

  ut::same<_0, emp::min0<e>>();
  ut::same<_1, emp::min<seq_1_2_3>>();
  ut::same<_3, emp::max<seq_1_2_3>>();
  ut::same<_1, abs<>::f<_1>>();
  ut::same<_1, abs<>::f<number<(-1)>>>();
  ut::same<_1, emp::pow<seq_1_2_3>>();
  ut::same<_0, emp::pow<seq_0_1_2>>();
  ut::same<number<8*8*8*8>, emp::pow<seq_2_3_4>>();

  test_pack<min, less<>>().test_unary();
  test_pack<abs, less<>>().test_unary();
  test_pack<pow>().test_unary();

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, detail::sfinae<g>>();
  };

  ctx(min<>())
    .test<_1, seq_1_2_3>()
    .test<bad_number, seq_bad>()
    .not_invocable<e>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(min0<>())
    .test<_1, seq_1_2_3>()
    .test<_0, e>()
    .test<bad_number, seq_bad>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(max<>())
    .test<_3, seq_1_2_3>()
    .test<bad_number, seq_bad>()
    .not_invocable<e>()
    .not_invocable<seq_bad_bad>()
    ;

  ctx(max0<>())
    .test<_3, seq_1_2_3>()
    .test<bad_number, seq_bad>()
    .test<_0, e>()
    .not_invocable<seq_bad_bad>()
    ;

  test_context<clamp_c<-2, 5>, smp::clamp_c<-2, 5>>()
    .test<_1, _1>()
    .test<_4, _4>()
    .test<_5, _5>()
    .test<_5, _6>()
    .test<number<-1>, number<-1>>()
    .test<number<-2>, number<-2>>()
    .test<number<-2>, number<-3>>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  test_context<abs<>, smp::abs<>>()
    .test<_1, _1>()
    .test<_1, number<(-1)>>()
    .not_invocable<>()
    .not_invocable<_1, _2>()
    .not_invocable<bad_number>()
    ;

  test_context<pow<>, smp::pow<>>()
    .test<_0, _0>()
    .test<_1, _1>()
    .test<_0, _0, _1>()
    .test<_1, _0, _0>()
    .test<number<8*8*8*8>, _2, _3, _4>()
    .not_invocable<_0, bad_number>()
    .not_invocable<_0, bad_number, bad_number>()
    ;

  ut::not_invocable<smp::pow<bad_function>>();
  ut::not_invocable<smp::pow<bad_function>, _1, _1, _1>();
}

TEST_SUITE_END()
