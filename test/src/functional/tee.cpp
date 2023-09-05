// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/tee.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class, class, class>
  using f = int;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_mulary_pack<tee>();
  (void)tee<identity, ut::unary>();
  (void)tee<identity, ut::listify>();
  (void)tee<identity, identity, ut::binary>();
  (void)tee<identity, identity, ut::listify>();
  (void)tee<identity, identity, identity, ut::listify>();
  test_mulary_pack<tee, identity, identity, identity, identity>();

  ut::same<int, tee<identity, identity, identity, identity, foo>::template f<void>>();

  test_context<tee<inc<>, dec<>, listify>, smp::tee<smp::inc<>, smp::dec<>, smp::listify>>()
    .test<list<_2, _0>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  test_context<
    tee<inc<>, inc<>, inc<>, inc<>, listify>,
    smp::tee<smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::listify>
  >()
    .test<list<_2, _2, _2, _2>, _1>()
    .not_invocable<>()
    .not_invocable<_0, _0>()
    ;

  test_context<tee<listify>, smp::tee<smp::listify>>()
    .test<list<>>()
    .test<list<>, _1>()
    ;

  ut::not_invocable<smp::tee<
    smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, smp::inc<>, foo
  >, _1>();

  ut::not_invocable<smp::tee<smp::always<na>, smp::listify>>();
  ut::not_invocable<smp::tee<bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, listify>>();
  ut::not_invocable<smp::tee<bad_function, bad_function, bad_function, bad_function>>();
  ut::not_invocable<smp::lift<smp::tee>>();
}

TEST_SUITE_END()
