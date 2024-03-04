// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/utility/unpack.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<unpack>();
  test_mulary_pack<unpack_append>();

  ut::same<_3, emp::unpack<seq_0_0_0, size<>>>();
  ut::same<_3, emp::unpack_append<seq_0_0_0, size<>>>();

  ut::same<seq_0_1, emp::unpack<seq_0_1, ut::binary>>();
  ut::same<seq_1_0, emp::unpack<seq_0, ut::binary, _1>>();
  ut::same<seq_0_1, emp::unpack_append<seq_0_1, ut::binary>>();
  ut::same<seq_0_1, emp::unpack_append<seq_0, ut::binary, _1>>();

  ut::same<seq_0_1, emp::unpack_c<seq_0_1, ut::binary>>();
  ut::same<seq_1_0, emp::unpack_c<seq_0, ut::binary, 1>>();
  ut::same<seq_0_1, emp::unpack_append_c<seq_0_1, ut::binary>>();
  ut::same<seq_0_1, emp::unpack_append_c<seq_0, ut::binary, 1>>();

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

#if JLN_MP_ENABLE_TPL_AUTO
struct foo_t_i { template<class, int...> struct f; };
struct foo_i_t { template<int, class...> struct f; };
struct foo_2t_i { template<class, class, int...> struct f; };
struct foo_2i_t { template<int, int, class...> struct f; };

template<int...>
struct vv {};

struct mk_vv { template<int... i> using f = vv<i...>; };

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  using v0 = vv<>;
  using v1 = vv<1>;
  using v2 = vv<1, 2>;

  ut::same<v0, emp::unpack_v<v0, mk_vv>>();
  ut::same<v1, emp::unpack_v<v1, mk_vv>>();
  ut::same<v2, emp::unpack_v<v2, mk_vv>>();
  ut::same<foo_t_i::f<_3, 1, 2>, emp::unpack_v<v2, foo_t_i, _3>>();
  ut::same<foo_2t_i::f<_3, _4, 1, 2>, emp::unpack_v<v2, foo_2t_i, _3, _4>>();

  ut::same<v0, emp::unpack_append_v<v0, mk_vv>>();
  ut::same<v1, emp::unpack_append_v<v1, mk_vv>>();
  ut::same<v2, emp::unpack_append_v<v2, mk_vv>>();
  ut::same<foo_2i_t::f<1, 2, _2, _3>, emp::unpack_append_v<v2, foo_2i_t, _2, _3>>();
}
#endif

TEST_SUITE_END()
