#include "test.hpp"

#include "jln/mp/smp/list/as_list.hpp"

TEST_SUITE_BEGIN()

template<class, class, class>
struct fake_list;

template<class...>
struct other_list;

TEST()
{
  using namespace jln::mp;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, as_list<>, t::uncallable>()
    .test<t::uncallable::f<>, as_list<>, z::seq<int, int>>()
    .test<z::optimized_result_t<t::any_list, as_list<>>, as_list<>, int>()
    .test<z::optimized_result_t<list<>, always<list<>>>, as_list<>, list<>>()
    .test<z::optimized_result_t<z::list_t<t::number>, identity>, as_list<>, z::list_t<t::number>>()
    .test<z::optimized_result_t<t::any_list, as_list<>>, as_list<>, t::any>()
    .test<z::optimized_result_t<t::basic_union<t::uncallable, t::any_list>, as_list<>>,
      as_list<>, z::pack<t::any>>()
    ;

  test_unary_pack<as_list>();

  using l1 = list<int, char, void>;
  using l2 = fake_list<int, char, void>;
  using l3 = other_list<int, char, void>;

  ut::same<l1, emp::as_list<l1>>();
  ut::same<l1, emp::as_list<l2>>();
  ut::same<l1, emp::as_list<l3>>();

  class bad;

  test_context<as_list<>, smp::as_list<>>()
    .test<l1, l1>()
    .test<l1, l2>()
    .test<l1, l3>()
    .not_invocable<>()
    .not_invocable<bad>()
    .not_invocable<l1, l1>()
    ;

  ut::not_invocable<smp::as_list<bad_function>>();
  ut::not_invocable<smp::as_list<bad_function>, list<>>();
}

TEST_SUITE_END()
