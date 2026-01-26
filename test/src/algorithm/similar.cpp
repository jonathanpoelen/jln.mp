// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.hpp"

#include "jln/mp/smp/algorithm/similar.hpp"
#include "jln/mp/smp/number/not.hpp"

TEST_SUITE_BEGIN()

template<class> class t1;
template<class, class> class t2;
template<class...> class tx;

template<std::size_t> class a1;
template<std::size_t, std::size_t> class a2;
template<std::size_t...> class ax;

template<class, std::size_t> class ta1;
template<class, std::size_t, std::size_t> class ta2;
template<class, std::size_t...> class tax;

template<std::size_t, class> class at1;
template<std::size_t, class, class> class at2;
template<std::size_t, class...> class atx;

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
template<auto> class va1;
template<auto, auto> class va2;
template<auto...> class vax;

template<class, auto> class vta1;
template<class, auto, auto> class vta2;
template<class, auto...> class vtax;

template<auto, class> class vat1;
template<auto, class, class> class vat2;
template<auto, class...> class vatx;
#endif

template<class T, T> class p1;
template<class T, T, T> class p2;
template<class T, T...> class px;

TEST()
{
  using namespace jln::mp;

  ut::same<true_, emp::similar<list<int, int, int>>>();
  ut::same<true_, emp::similar<list<list<>, list<int>, list<char, short>>>>();
  ut::same<false_, emp::similar<list<int, int, void>>>();

  ut::same<true_, number<emp::similar_v<list<int, int, int>>>>();
  ut::same<true_, number<emp::similar_v<list<list<>, list<int>, list<char, short>>>>>();
  ut::same<false_, number<emp::similar_v<list<int, int, void>>>>();

  ut::same<true_, number<emp::similar_xs_v<int, int, int>>>();
  ut::same<true_, number<emp::similar_xs_v<list<>, list<int>, list<char, short>>>>();
  ut::same<false_, number<emp::similar_xs_v<int, int, void>>>();

  test_unary_pack<similar>();

#if JLN_MP_ENABLE_TPL_PARAM_AUTO
  constexpr std::size_t i1 = 1;
  constexpr std::size_t i2 = 2;
#endif

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
    // check ambiguity
    .test<true_, t1<int>, t1<char>>()
    .test<true_, t2<int, int>, t2<int, char>>()
    .test<true_, tx<>, tx<int>, tx<int, int>, tx<int, int, int>>()
    .test<true_, a1<1>, a1<2>>()
#if JLN_MP_ENABLE_TPL_PARAM_AUTO
    .test<true_, a2<1, 1>, a2<2, 2>>()
    .test<true_, ax<1>, ax<1, 2>>()
#endif
    .test<true_, ta1<int, 1>, ta1<int, 2>>()
    .test<true_, ta2<int, 1, 1>, ta2<int, 2, 2>>()
    .test<true_, tax<int, 1, 1>, tax<int, 1>>()
    .test<true_, at1<1, int>, at1<2, int>>()
    .test<true_, at2<1, int, int>, at2<2, int, int>>()
    .test<true_, atx<1>, atx<1, int>>()
#if JLN_MP_ENABLE_TPL_PARAM_AUTO
    .test<true_, va1<1>, va1<2>>()
    .test<true_, va2<1, 1>, va2<2, 2>>()
    .test<true_, vax<1>, vax<1, 2>>()
    .test<true_, vta1<int, 1>, vta1<int, 2>>()
    .test<true_, vta2<int, 1, 1>, vta2<int, 2, 2>>()
    .test<true_, vtax<int, 1, 1>, vtax<int, 1>>()
    .test<true_, vat1<1, int>, vat1<2, int>>()
    .test<true_, vat2<1, int, int>, vat2<2, int, int>>()
    .test<true_, vatx<1>, vatx<1, int>>()
    .test<true_, va1<i1>, va1<i2>>()
    .test<true_, va2<i1, i1>, va2<i2, i2>>()
    .test<true_, vax<i1>, vax<i1, i2>>()
    .test<true_, vta1<int, i1>, vta1<int, i2>>()
    .test<true_, vta2<int, i1, i1>, vta2<int, i2, i2>>()
    .test<true_, vtax<int, i1, i1>, vtax<int, i1>>()
    .test<true_, vat1<i1, int>, vat1<i2, int>>()
    .test<true_, vat2<i1, int, int>, vat2<i2, int, int>>()
    .test<true_, vatx<i1>, vatx<i1, int>>()
#endif
    .test<true_, p1<int, 1>, p1<int, 2>>()
    .test<true_, p2<int, 1, 1>, p2<int, 2, 2>>()
    .test<true_, px<int>, px<int, 1>>()
    .test<true_, px<int, 1>, px<int, 1, 2>>()
    .test<false_
      , t1<int>, t2<int, int>, tx<>, tx<int>, tx<int, int>, tx<int, int, int>
      , a1<1>, a2<1, 1>, ax<>, ax<1>, ax<1, 1>, ax<1, 1, 1>
      , ta1<int, 1>, ta2<int, 1, 1>, tax<int>, tax<int, 1>, tax<int, 1, 1>, tax<int, 1, 1, 1>
      , at1<1, int>, at2<1, int, int>, atx<1>, atx<1, int>, atx<1, int, int>, atx<1, int, int, int>
      #if JLN_MP_ENABLE_TPL_PARAM_AUTO
      , vta1<int, 1>, vta2<int, 1, 1>, vtax<int>, vtax<int, 1>, vtax<int, 1, 1>, vtax<int, 1, 1, 1>
      , vat1<1, int>, vat2<1, int, int>, vatx<1>, vatx<1, int>, vatx<1, int, int>, vatx<1, int, int, int>
      , vta1<int, i1>, vta2<int, i1, i1>, vtax<int>, vtax<int, i1>, vtax<int, i1, i1>, vtax<int, i1, i1, i1>
      , vat1<i1, int>, vat2<i1, int, int>, vatx<i1>, vatx<i1, int>, vatx<i1, int, int>, vatx<i1, int, int, int>
      #endif
      , p1<int, 1>, p2<int, 1, 1>, px<int>, px<int, 1>, px<int, 1, 1>, px<int, 1, 1, 1>
    >()
    ;

  test_context<similar<not_<>>, smp::similar<smp::not_<>>>()
    .test<false_>()
    .test<false_, int>()
    .test<false_, int, int>()
    .test<true_, int, float>()
    ;

  ut::not_invocable<smp::similar<bad_function>>();
  ut::not_invocable<smp::similar<bad_function>, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void>();
  ut::not_invocable<smp::similar<bad_function>, void, void, void>();
}

TEST_SUITE_END()
