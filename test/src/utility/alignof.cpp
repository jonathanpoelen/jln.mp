#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/alignof.hpp"

TEST_SUITE_BEGIN()

template<std::size_t n>
struct alignas(n) aligned {};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_1, emp::alignof_<aligned<1>>>();
  ut::same<_2, emp::alignof_<aligned<2>>>();
  ut::same<_4, emp::alignof_<aligned<4>>>();

  test_context<alignof_<>, smp::alignof_<>>()
    .test<_1, aligned<1>>()
    .test<_8, aligned<8>>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::alignof_<>, void>();
  ut::not_invocable<smp::alignof_<bad_function>>();
  ut::not_invocable<smp::alignof_<bad_function>, size<>>();
}

TEST_SUITE_END()
