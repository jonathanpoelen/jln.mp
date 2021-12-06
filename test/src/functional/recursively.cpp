#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/recursively.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/number/operators.hpp"
#include "jln/mp/smp/utility/unpack.hpp"

TEST_SUITE_BEGIN()

template<int n, class Stop = jln::mp::stop_recursion, class Next = jln::mp::identity>
using until_n_c = jln::mp::if_<
  jln::mp::less_than_c<n>,
  jln::mp::inc<Next>,
  Stop
>;

template<
  template<class...> class Mp,
  template<class...> class Smp>
void test_rec()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_3, call<Mp<until_n_c<3>>, _0>>();

  test_pack2<Mp, identity>();

  using detail::sfinae;

  test_context<Mp<until_n_c<3>>, Smp<sfinae<until_n_c<3>>>>()
    .template test<_3, _0>()
    .template test<_3, _1>()
    .template test<_3, _2>()
    .template test<_3, _3>()
    .template test<_4, _4>()
    .template test<_10, _10>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;

  test_context<Mp<until_n_c<10>>, Smp<sfinae<until_n_c<10>>>>()
    .template test<_10, _2>()
    .template test<_10, _10>()
    .template test<_11, _11>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;

  using test_next_recursion = until_n_c<10, stop_recursion, next_recursion>;
  test_context<Mp<test_next_recursion>, Smp<sfinae<test_next_recursion>>>()
    .template test<_10, _2>()
    .template test<_10, _10>()
    .template test<_11, _11>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;

  using f = push_back<_2, mul<recursion_result>>;
  test_context<Mp<until_n_c<10, f>>, Smp<sfinae<until_n_c<10, f>>>>()
    .template test<_20, _2>()
    .template test<_20, _10>()
    .template test<_22, _11>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;

  ut::not_invocable<Smp<sfinae<until_n_c<3>>, bad_function>>();
  ut::not_invocable<Smp<sfinae<until_n_c<15>>, bad_function>>();
  ut::not_invocable<Smp<bad_function, bad_function>>();
  ut::not_invocable<Smp<sfinae<until_n_c<10,
    smp::always<list<_0, _0>, smp::unpack<smp::recursion_result>>>>>>();
}

TEST()
{
  using namespace jln::mp;

  test_rec<recursively, smp::recursively>();
  test_rec<recursively_as_much_as_possible, smp::recursively_as_much_as_possible>();
}

TEST_SUITE_END()
