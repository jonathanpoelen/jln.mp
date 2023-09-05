// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/algorithm/similar.hpp"

TEST_SUITE_BEGIN()

template<class> class t1;
template<class, class> class t2;
template<class...> class tx;

template<JLN_MP_TPL_AUTO_OR(std::size_t)> class a1;
template<JLN_MP_TPL_AUTO_OR(std::size_t), JLN_MP_TPL_AUTO_OR(std::size_t)> class a2;
template<JLN_MP_TPL_AUTO_OR(std::size_t)...> class ax;

template<class, JLN_MP_TPL_AUTO_OR(std::size_t)> class ta1;
template<class, JLN_MP_TPL_AUTO_OR(std::size_t), JLN_MP_TPL_AUTO_OR(std::size_t)> class ta2;
template<class, JLN_MP_TPL_AUTO_OR(std::size_t)...> class tax;

template<JLN_MP_TPL_AUTO_OR(std::size_t), class> class at1;
template<JLN_MP_TPL_AUTO_OR(std::size_t), class, class> class at2;
template<JLN_MP_TPL_AUTO_OR(std::size_t), class...> class atx;

template<class T, T> class p1;
template<class T, T, T> class p2;
template<class T, T...> class px;

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::similar<list<int, int, int>>>();
  ut::same<true_, emp::similar<list<list<>, list<int>, list<char, short>>>>();
  ut::same<false_, emp::similar<list<int, int, void>>>();

  test_unary_pack<similar>();

  test_context<similar<>, smp::similar<>>()
    .test<true_>()
    .test<true_, int>()
    .test<true_, int, int>()
    .test<true_, int, int, int>()
    .test<true_, list<>>()
    .test<true_, list<>, list<>>()
    .test<true_, list<>, list<int>>()
    .test<false_, int, void>()
    .test<false_, int, int, void>()
    .test<false_, int, int, list<int>>()
    .test<false_, similar<>, list<>>()
    .test<true_
      , tx<>, tx<int>, tx<int, int>, tx<int, int, int>
    >()
    // check ambiguity
    .test<false_
      , t1<int>, t2<int, int>, tx<>, tx<int>, tx<int, int>, tx<int, int, int>
      , a1<1>, a2<1, 1>, ax<>, ax<1>, ax<1, 1>, ax<1, 1, 1>
      , ta1<int, 1>, ta2<int, 1, 1>, tax<int>, tax<int, 1>, tax<int, 1, 1>, tax<int, 1, 1, 1>
      , at1<1, int>, at2<1, int, int>, atx<1>, atx<1, int>, atx<1, int, int>, atx<1, int, int, int>
      , p1<int, 1>, p2<int, 1, 1>, px<int>, px<int, 1>, px<int, 1, 1>, px<int, 1, 1, 1>
    >()
    ;

  ut::not_invocable<smp::similar<bad_function>>();
  ut::not_invocable<smp::similar<bad_function>, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void, void>();
}

TEST_SUITE_END()
