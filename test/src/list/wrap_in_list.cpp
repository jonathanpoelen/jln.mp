#include "test.hpp"

#include "jln/mp/smp/list/wrap_in_list.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/utility/is.hpp"

#include <type_traits>

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;

  using pred1 = is<int>;
  using pred2 = lift<std::is_same>;

  ut::same<list<int>, emp::wrap_in_list_if<pred1, int>>();
  ut::same<list<>, emp::wrap_in_list_if<pred1, char>>();
  ut::same<list<int>, emp::wrap_in_list_if<pred2, int, int>>();
  ut::same<list<>, emp::wrap_in_list_if<pred2, int, char>>();

  ut::same<list<>, emp::wrap_in_list_if_not<pred1, int>>();
  ut::same<list<char>, emp::wrap_in_list_if_not<pred1, char>>();
  ut::same<list<>, emp::wrap_in_list_if_not<pred2, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<pred2, int, char>>();

  test_context<wrap_in_list_if<pred1>, smp::wrap_in_list_if<pred1>>()
    .test<list<int>, int>()
    .test<list<>, char>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<wrap_in_list_if<pred2>, smp::wrap_in_list_if<pred2>>()
    .test<list<int>, int, int>()
    .test<list<>, int, char>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  test_context<wrap_in_list_if_not<pred1>, smp::wrap_in_list_if_not<pred1>>()
    .test<list<>, int>()
    .test<list<char>, char>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  test_context<wrap_in_list_if_not<pred2>, smp::wrap_in_list_if_not<pred2>>()
    .test<list<>, int, int>()
    .test<list<int>, int, char>()
    .not_invocable<>()
    .not_invocable<int>()
    .not_invocable<int, int, int>()
    ;

  ut::not_invocable<smp::wrap_in_list_if<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if<always<void>>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<always<void>>, int, int>();
}

TEST_SUITE_END()
