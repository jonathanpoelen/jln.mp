#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;
  namespace z = optimizer;
  namespace t = optimizer::types;

  test_context<lift<z::optimize>, void>()
    .test<t::uncallable::f<>, unpack<listify>, t::uncallable>()
    .test<t::uncallable::f<>, unpack<listify>, int>()
    .test<t::uncallable::f<>, unpack<listify>, z::seq<int, int>>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>,
      unpack<listify>, list<int>>()
    .test<z::optimized_result_t<list<void, int>, always<list<void, int>>>,
      unpack<listify>, z::seq<list<int>, void>>()
    .test<z::optimized_result_t<z::list_t<t::number, int>, unpack<listify>>,
      unpack<listify>, z::seq<list<int>, t::number>>()
    .test<z::optimized_result_t<z::list_t<t::number>, unpack<listify>>,
      unpack<listify>, z::list_t<t::number>>()
    .test<z::optimized_result_t<z::list_t<z::pack<t::any>>, unpack<listify>>,
      unpack<listify>, z::list_t<z::pack<t::any>>>()
    .test<z::optimized_result_t<z::list_t<int, z::pack<t::any>>, unpack<listify>>,
      unpack<listify>, z::seq<z::list_t<z::pack<t::any>>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<t::number>>,
                                unpack<listify>>,
      unpack<listify>, z::union_<z::list_t<t::number>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<t::number>>,
                                unpack<listify>>,
      unpack<listify>, z::union_<t::uncallable, z::list_t<t::number>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<z::pack<void>, t::number>>,
                                unpack<listify>>,
      unpack<listify>, z::seq<z::union_<t::uncallable, z::list_t<t::number>, int>, z::pack<void>>>()

    // unpack_append
    .test<t::uncallable::f<>, unpack_append<listify>, t::uncallable>()
    .test<t::uncallable::f<>, unpack_append<listify>, int>()
    .test<t::uncallable::f<>, unpack_append<listify>, z::seq<int, int>>()
    .test<z::optimized_result_t<list<int>, always<list<int>>>,
      unpack_append<listify>, list<int>>()
    .test<z::optimized_result_t<list<int, void>, always<list<int, void>>>,
      unpack_append<listify>, z::seq<list<int>, void>>()
    .test<z::optimized_result_t<z::list_t<int, t::number>, unpack_append<listify>>,
      unpack_append<listify>, z::seq<list<int>, t::number>>()
    .test<z::optimized_result_t<z::list_t<t::number>, unpack_append<listify>>,
      unpack_append<listify>, z::list_t<t::number>>()
    .test<z::optimized_result_t<z::list_t<z::pack<t::any>>, unpack_append<listify>>,
      unpack_append<listify>, z::list_t<z::pack<t::any>>>()
    .test<z::optimized_result_t<z::list_t<z::pack<t::any>, int>, unpack_append<listify>>,
      unpack_append<listify>, z::seq<z::list_t<z::pack<t::any>>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<t::number>>,
                                unpack_append<listify>>,
      unpack_append<listify>, z::union_<z::list_t<t::number>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<t::number>>,
                                unpack_append<listify>>,
      unpack_append<listify>, z::union_<t::uncallable, z::list_t<t::number>, int>>()
    .test<z::optimized_result_t<z::union_<t::uncallable, z::list_t<t::number, z::pack<void>>>,
                                unpack_append<listify>>,
      unpack_append<listify>, z::seq<z::union_<t::uncallable, z::list_t<t::number>, int>, z::pack<void>>>()
    ;

  test_mulary_pack<unpack>();
  test_mulary_pack<unpack_append>();

  ut::same<_3, emp::unpack<seq_0_0_0, size<>>>();
  ut::same<_3, emp::unpack_append<seq_0_0_0, size<>>>();

  ut::same<seq_0_1, emp::unpack<seq_0_1, ut::binary>>();
  ut::same<seq_1_0, emp::unpack<seq_0, ut::binary, _1>>();
  ut::same<seq_0_1, emp::unpack_append<seq_0_1, ut::binary>>();
  ut::same<seq_0_1, emp::unpack_append<seq_0, ut::binary, _1>>();

  test_context<unpack<size<>>, smp::unpack<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<unpack_append<size<>>, smp::unpack_append<smp::size<>>>()
    .test<_0, list<>>()
    .test<_1, seq_1>()
    .test<_3, seq_0_0_0>()
    .test<_4, seq_0_0_0, _0>()
    .not_invocable<>()
    .not_invocable<_0>()
    ;

  test_context<unpack<listify>, smp::unpack<smp::listify>>()
    .test<list<_3, _0, _1, _2>, seq_0_1_2, _3>()
    ;

  test_context<unpack_append<listify>, smp::unpack_append<smp::listify>>()
    .test<seq_0_1_2_3, seq_0_1_2, _3>()
    ;

  test_context<unpack<identity>, smp::unpack<smp::identity>>()
    .test<_0, seq_0>()
    .not_invocable<seq_0_1>()
    ;

  test_context<unpack_append<identity>, smp::unpack_append<smp::identity>>()
    .test<_0, seq_0>()
    .not_invocable<seq_0_1>()
    ;

  ut::not_invocable<smp::unpack<bad_function>>();
  ut::not_invocable<smp::unpack<bad_function>, list<>>();
  ut::not_invocable<smp::unpack_append<bad_function>>();
  ut::not_invocable<smp::unpack_append<bad_function>, list<>>();
}

TEST_SUITE_END()
