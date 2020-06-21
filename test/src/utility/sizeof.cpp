#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/sizeof.hpp"

TEST_SUITE_BEGIN()

template<std::size_t n>
using of_size = char[n];

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_1, emp::sizeof_<of_size<1>>>();
  ut::same<_2, emp::sizeof_<of_size<2>>>();
  ut::same<_3, emp::sizeof_<of_size<3>>>();

  test_context<sizeof_<>, smp::sizeof_<>>()
    .test<_1, of_size<1>>()
    .test<_6, of_size<6>>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::sizeof_<>, void>();
  ut::not_invocable<smp::sizeof_<bad_function>>();
  ut::not_invocable<smp::sizeof_<bad_function>, size<>>();
}

TEST_SUITE_END()
