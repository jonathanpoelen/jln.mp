#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/algorithm/sort.hpp"

TEST_SUITE_BEGIN()

struct cmp_err
{
  template<class x, class y>
  using f = typename jln::mp::conditional_c<(x::value % 2) == (y::value % 2)>
    ::template f<jln::mp::number<(x::value < y::value)>, int>;
};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<list<>, call<sort<>>>();

  ut::same<seq_0, call<sort<>, _0>>();

  ut::same<seq_0_1, call<sort<>, _0, _1>>();
  ut::same<seq_0_1, call<sort<>, _1, _0>>();

  ut::same<seq_0_1_2, call<sort<>, _0, _1, _2>>();
  ut::same<seq_0_1_2, call<sort<>, _1, _0, _2>>();
  ut::same<seq_0_1_2, call<sort<>, _0, _2, _1>>();
  ut::same<seq_0_1_2, call<sort<>, _1, _2, _0>>();
  ut::same<seq_0_1_2, call<sort<>, _2, _0, _1>>();
  ut::same<seq_0_1_2, call<sort<>, _2, _1, _0>>();

  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _1, _2, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _0, _2, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _2, _1, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _2, _0, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _0, _1, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _1, _0, _3>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _1, _3, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _0, _3, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _2, _3, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _2, _3, _0>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _0, _3, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _1, _3, _0>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _3, _1, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _3, _0, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _0, _3, _2, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _1, _3, _2, _0>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _3, _0, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _2, _3, _1, _0>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _0, _1, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _1, _0, _2>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _0, _2, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _1, _2, _0>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _2, _0, _1>>();
  ut::same<list<_0, _1, _2, _3>, call<sort<>, _3, _2, _1, _0>>();

  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _2, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _2, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _1, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _0, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _1, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _0, _3, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _3, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _3, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _3, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _3, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _3, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _3, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _1, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _0, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _2, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _2, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _0, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _1, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _1, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _0, _2, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _2, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _2, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _0, _1, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _1, _0, _4>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _2, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _2, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _1, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _0, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _1, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _0, _4, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _3, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _3, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _3, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _3, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _3, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _3, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _1, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _0, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _2, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _2, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _0, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _1, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _1, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _0, _4, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _2, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _2, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _0, _4, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _1, _4, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _4, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _4, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _4, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _4, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _4, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _4, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _1, _4, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _0, _4, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _2, _4, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _2, _4, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _0, _4, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _1, _4, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _4, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _4, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _3, _4, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _3, _4, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _4, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _3, _4, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _4, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _4, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _0, _4, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _1, _4, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _4, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _2, _4, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _1, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _0, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _2, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _2, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _0, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _1, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _1, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _0, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _2, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _2, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _0, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _1, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _3, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _3, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _0, _4, _3, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _1, _4, _3, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _3, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _2, _4, _3, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _0, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _1, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _0, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _1, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _2, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _3, _4, _2, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _1, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _0, _2, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _2, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _2, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _0, _1, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _1, _0, _3>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _1, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _0, _3, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _2, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _2, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _0, _3, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _1, _3, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _3, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _3, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _0, _3, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _1, _3, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _3, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _2, _3, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _0, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _1, _0, _2>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _0, _2, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _1, _2, _0>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _2, _0, _1>>();
  ut::same<list<_0, _1, _2, _3, _4>, call<sort<>, _4, _3, _2, _1, _0>>();

  ut::same<list<_0, _1, _2, _3, _4, _5>, call<sort<>, _0, _1, _2, _3, _4, _5>>();
  ut::same<list<_0, _1, _2, _3, _4, _5>, call<sort<>, _4, _3, _5, _0, _1, _2>>();
  ut::same<list<_0, _1, _2, _3, _4, _5>, call<sort<>, _5, _4, _3, _2, _1, _0>>();

  ut::same<list<_0, _1, _2, _3, _4, _5, _6>, call<sort<>, _0, _1, _2, _3, _4, _5, _6>>();
  ut::same<list<_0, _1, _2, _3, _4, _5, _6>, call<sort<>, _6, _5, _4, _3, _2, _1, _0>>();
  ut::same<list<_0, _1, _2, _3, _4, _5, _6>, call<sort<>, _2, _6, _3, _1, _4, _0, _5>>();

  ut::same<list<
    _1, _2, _5, _5, _6, _6, _9, _9, _11, _13, _15, _16,
    _17, _19, _21, _22, _22, _23, _26, _26, _30
  >, call<sort<>,
    _11, _16, _5, _19, _2, _30, _17, _15, _26, _9, _22,
    _6, _13, _6, _21, _22, _5, _9, _23, _26, _1>
  >();

  ut::same<list<
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
    _60, _61, _62, _63, _64, _65, _66, _67, _68, _69,
    _70, _71, _72, _73, _74, _75, _76, _77, _78, _79,
    _80, _81, _82, _83, _84, _85, _86, _87, _88, _89,
    _90, _91, _92, _93, _94, _95, _96, _97, _98, _99,
    _100, _101, _102, _103, _104, _105, _106, _107, _108, _109
  >, call<sort<>,
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39,
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59,
    _60, _61, _62, _63, _64, _65, _66, _67, _68, _69,
    _70, _71, _72, _73, _74, _75, _76, _77, _78, _79,
    _80, _81, _82, _83, _84, _85, _86, _87, _88, _89,
    _90, _91, _92, _93, _94, _95, _96, _97, _98, _99,
    _100, _101, _102, _103, _104, _105, _106, _107, _108, _109
  >>();

  ut::not_invocable<smp::sort<cmp_err>, _0, _0, _0, _1, _1, _1>();

  test_pack2<sort>();
  test_pack2<sort, listify>();

  ut::same<seq_1_2_3, emp::sort<seq_3_2_1>>();

  test_context<sort<>, smp::sort<>>()
    .test<list<>>()
    .test<list<_0>, _0>()
    .test<list<_0, _1>, _1, _0>()
    .test<list<_0, _0, _0, _0, _0, _1, _1, _1, _1, _1, _1>,
      _1, _0, _0, _0, _0, _1, _0, _1, _1, _1, _1>()
    .test<list<bad_number>, bad_number>()
    .not_invocable<bad_number, bad_number>()
    .not_invocable<bad_number, bad_number, bad_number>()
    .not_invocable<_0, _0, bad_number>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0, _0, bad_number, _0, _0, _0>()
    .not_invocable<_0, _0, _0, _0, _0, _0, _0, _0, bad_number, _0, _0, _0, _0>()
    ;

  ut::not_invocable<smp::sort<bad_function>, _1, _1>();
  ut::not_invocable<smp::sort<bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::sort<bad_function>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sort<always<void>>, _1, _1, _1, _1>();
  ut::not_invocable<smp::sort<bad_function, bad_function>, _1>();
  ut::not_invocable<smp::sort<bad_function, bad_function>, _1, _1>();
  ut::not_invocable<smp::sort<bad_function, bad_function>, _1, _1, _1>();
  ut::not_invocable<smp::sort<bad_function, bad_function>, _1, _1, _1, _1>();
}

TEST_SUITE_END()
