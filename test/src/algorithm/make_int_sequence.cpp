#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/algorithm/make_int_sequence.hpp"
#include "jln/mp/number/numbers.hpp"
#include "jln/mp/list/size.hpp"

TEST_SUITE_BEGIN(make_int_sequence)

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  using a = emp::numbers<>;
  using b = emp::numbers<0>;
  using c = emp::numbers<0, 1>;
  using d = emp::numbers<0, 1, 2>;
  using e = emp::numbers<0, 1, 2, 3>;

  emp::make_int_sequence<_0>() = a();
  emp::make_int_sequence<_1>() = b();
  emp::make_int_sequence<_2>() = c();
  emp::make_int_sequence<_3>() = d();
  emp::make_int_sequence<_4>() = e();

  test_pack<make_int_sequence>()
    .test_unary<_1>()
    .test_binary<_2>()
  ;

  test_context<make_int_sequence<>, smp::make_int_sequence<>>()
    .test<a, _0>()
    .test<b, _1>()
    .test<c, _2>()
    .test<d, _3>()
    .test<e, _4>()
    .not_invocable<e>()
    .not_invocable<class X>()
    ;
  test_context<make_int_sequence<size<make_int_sequence<>>>, smp::make_int_sequence<smp::size<smp::make_int_sequence<>>>>()
    .test<a, _0>()
    .test<b, _1>()
    .test<c, _2>()
    .test<d, _3>()
    .test<e, _4>()
    .not_invocable<e>()
    .not_invocable<class X>()
    ;
}

TEST_SUITE_END()
