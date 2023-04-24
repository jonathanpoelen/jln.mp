#include "test.hpp"

#include "jln/mp/smp/list/wrap_in_list.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/utility/always.hpp"
#include "jln/mp/smp/utility/is_not.hpp"

#include <type_traits>

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  namespace z = optimizer;
  namespace t = optimizer::types;

  using w_is_int = wrap_in_list_if<is<int>>;
  using w_always_int = wrap_in_list_if<always<true_>>;
  using w0 = wrap_in_list_c<false>;
  using w1 = wrap_in_list_c<true>;
  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, w_is_int, t::uncallable>()
    .test<t::uncallable::f<>, w_is_int, z::seq<int, int>>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>, w_is_int, int>()
    .test<z::optimized_result_t<z::union_<t::uncallable, list<int>>, always<list<int>>>,
      w_is_int, z::union_<t::uncallable, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, t::basic_list<t::any>, list<>>, w_is_int>,
      w_is_int, z::union_<t::any, z::seq<int, int>>>()
    .test<z::optimized_result_t<list<>, always<list<>>>, w_is_int, void>()
    .test<z::optimized_result_t<z::union_<t::basic_list<t::number>, list<>>, w_is_int>,
      w_is_int, t::number>()
    .test<z::optimized_result_t<z::union_<t::uncallable, list<int>, list<>>, w_is_int>,
      w_is_int, t::basic_pack<int>>()
    .test<t::uncallable::f<>, w_always_int, t::uncallable>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>, w_always_int, int>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>, w_always_int, z::seq<int, int>>()
    // wrap_in_list_c
    .test<z::optimized_result_t<list<>, always<list<>>>, w0, int>()
    .test<z::optimized_result_t<list<>, always<list<>>>, w0, z::seq<int, long>>()
    .test<z::optimized_result_t<list<>, always<list<>>>, w0, z::seq<t::number, t::any>>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>, w1, int>()
    .test<z::optimized_result_t<list<int, long>, always<list<int, long>>>, w1, z::seq<int, long>>()
    .test<z::optimized_result_t<z::list_t<t::number, t::any>, wrap_in_list_c<true>>,
      w1, z::seq<t::number, t::any>>()
    ;

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

  ut::same<list<>, emp::wrap_in_list_if<is<int, not_<>>, int>>();
  ut::same<list<>, emp::wrap_in_list_if<lift<std::is_same, not_<>>, int, int>>();
  ut::same<list<>, emp::wrap_in_list_if<tee<is<int>, not_<>>, int>>();
  ut::same<list<>, emp::wrap_in_list_if<tee<lift<std::is_same>, not_<>>, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<is<int, not_<>>, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<lift<std::is_same, not_<>>, int, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<tee<is<int>, not_<>>, int>>();
  ut::same<list<int>, emp::wrap_in_list_if_not<tee<lift<std::is_same>, not_<>>, int, int>>();

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

  ut::not_invocable<smp::wrap_in_list_if<smp::always<number<2>>>, int>();
  ut::not_invocable<smp::wrap_in_list_if<smp::always<na>>, int>();
  ut::not_invocable<smp::wrap_in_list_if<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if<always<void>>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<smp::always<na>>>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>>();
  ut::not_invocable<smp::wrap_in_list_if_not<bad_function>, int, int>();
  ut::not_invocable<smp::wrap_in_list_if_not<always<void>>, int, int>();
}

TEST_SUITE_END()
