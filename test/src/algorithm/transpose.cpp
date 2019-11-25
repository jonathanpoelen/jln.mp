#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/transpose.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<
    list<
      emp::numbers<40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 410, 411, 412, 413, 414, 415, 416, 417, 418>,
      emp::numbers<30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 310, 311, 312, 313, 314, 315, 316, 317, 318>,
      emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18>
    >,
    emp::transpose<list<
      emp::numbers<40,  30, 0>, emp::numbers<41,  31, 1>,
      emp::numbers<42,  32, 2>, emp::numbers<43,  33, 3>,
      emp::numbers<44,  34, 4>, emp::numbers<45,  35, 5>,
      emp::numbers<46,  36, 6>, emp::numbers<47,  37, 7>,
      emp::numbers<48,  38, 8>, emp::numbers<49,  39, 9>,
      emp::numbers<410, 310, 10>, emp::numbers<411, 311, 11>,
      emp::numbers<412, 312, 12>, emp::numbers<413, 313, 13>,
      emp::numbers<414, 314, 14>, emp::numbers<415, 315, 15>,
      emp::numbers<416, 316, 16>, emp::numbers<417, 317, 17>,
      emp::numbers<418, 318, 18>
    >>
  >();

  test_pack<transpose>()
    .test_variadic()
    .test_binary()
    .test_unary()
    ;

  test_context<transpose<>, smp::transpose<>>()
    .test<list<>, list<>, list<>>()
    .test<list<list<_0, _1>>, list<_0>, list<_1>>()
    .test<list<list<_0, _2>, list<_1, _3>>,
      list<_0, _1>, list<_2, _3>>()
    .test<list<list<_0, _2, _4>, list<_1, _3, _5>>,
      list<_0, _1>, list<_2, _3>, list<_4, _5>>()
    .not_invocable<list<>, list<_0>>()
    .not_invocable<int>()
    ;
}

TEST_SUITE_END()
