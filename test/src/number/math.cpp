#include "test.hpp"

#include "jln/mp/smp/number/math.hpp"
#include "jln/mp/smp/number/numbers.hpp"

TEST_SUITE_BEGIN()

struct bad_number
{
  class a {};
  constexpr static a value {};
};

TEST()
{
  using namespace jln::mp;

  using _0 = number<0>;
  using _1 = number<1>;
  using _2 = number<2>;
  using _3 = number<3>;
  using _4 = number<4>;

  using e = list<>;
  using seq_0_1_2 = emp::numbers<0, 1, 2>;
  using seq_1_2_3 = emp::numbers<1, 2, 3>;
  using seq_2_3_4 = emp::numbers<2, 3, 4>;
  using bad_seq1 = list<bad_number>;
  using bad_seq2 = list<bad_number, bad_number>;

  IS_SAME(_0, emp::min0<e>);
  IS_SAME(_1, emp::min<seq_1_2_3>);
  IS_SAME(_3, emp::max<seq_1_2_3>);
  IS_SAME(_1, abs<>::f<_1>);
  IS_SAME(_1, abs<>::f<number<(-1)>>);
  IS_SAME(_1, emp::pow<seq_1_2_3>);
  IS_SAME(_0, emp::pow<seq_0_1_2>);
  IS_SAME(number<8*8*8*8>, emp::pow<seq_2_3_4>);

  test_pack<min>().test_unary();
  test_pack<abs>().test_unary();
  test_pack<pow>().test_unary();

  auto ctx = [](auto f){
    using g = unpack<decltype(f)>;
    return test_context<g, sfinae<g>>();
  };

  ctx(min<>())
    .test<_1, seq_1_2_3>()
    .test<bad_number, bad_seq1>()
    .not_invocable<e>()
    .not_invocable<bad_seq2>()
    ;

  ctx(min0<>())
    .test<_1, seq_1_2_3>()
    .test<_0, e>()
    .test<bad_number, bad_seq1>()
    .not_invocable<bad_seq2>()
    ;

  ctx(max<>())
    .test<_3, seq_1_2_3>()
    .test<bad_number, bad_seq1>()
    .not_invocable<e>()
    .not_invocable<bad_seq2>()
    ;

  ctx(max0<>())
    .test<_3, seq_1_2_3>()
    .test<bad_number, bad_seq1>()
    .test<_0, e>()
    .not_invocable<bad_seq2>()
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
}

TEST_SUITE_END()
