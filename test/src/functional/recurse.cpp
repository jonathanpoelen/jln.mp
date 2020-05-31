#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/recurse.hpp"
#include "jln/mp/smp/functional/lift.hpp"
#include "jln/mp/smp/functional/if.hpp"
#include "jln/mp/smp/number/operators.hpp"

TEST_SUITE_BEGIN()

template<int n>
struct until_rec_fix_c
{
  template<class F, class x>
  using f = typename jln::mp::emp::conditional_c<
    (x::value >= n),
    jln::mp::always<x>,
    F
  >::template f<jln::mp::number<x::value+1>>;
};

template<int n>
struct infinite_rec_fix_c
{
  template<class F, class x>
  using f = typename F::template f<jln::mp::number<x::value+(x::value < n)>>;
};

template<int n>
using until_rec_c = jln::mp::if_<
  jln::mp::less_than_c<n>,
  jln::mp::inc<>,
  jln::mp::lift<jln::mp::stop_iteration>
>;

template<int n>
using infinite_rec_c = jln::mp::if_<
  jln::mp::less_than_c<n>,
  jln::mp::inc<>,
  jln::mp::identity
>;

template<
  template<class...> class Mp,
  template<class...> class Smp,
  template<int> class MF,
  template<class...> class sfinae,
  int VerifySfinae = 1>
void test_rec()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_3, call<Mp<MF<3>>, _0>>();

  test_pack2<Mp, identity>();

  test_context<Mp<MF<3>>, Smp<sfinae<MF<3>>>, VerifySfinae>()
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

  test_context<Mp<MF<10>>, Smp<sfinae<MF<10>>>, VerifySfinae>()
    .template test<_10, _2>()
    .template test<_10, _10>()
    .template test<_11, _11>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;

  ut::not_invocable<Smp<MF<3>, bad_function>>();
  ut::not_invocable<Smp<MF<15>, bad_function>>();
  ut::not_invocable<Smp<bad_function, bad_function>>();
}

TEST()
{
  using namespace jln::mp;

  test_rec<recurse, smp::recurse, until_rec_c, detail::sfinae>();
  test_rec<recurse_fix, smp::recurse_fix, until_rec_fix_c, contract_barrier, -1>();
  test_rec<infinite_recurse, smp::infinite_recurse, infinite_rec_c, detail::sfinae>();
  test_rec<infinite_recurse_fix, smp::infinite_recurse_fix, infinite_rec_fix_c, contract_barrier, -1>();
}

TEST_SUITE_END()
