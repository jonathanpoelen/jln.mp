#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/recurse.hpp"
#include "jln/mp/smp/functional/bind.hpp"
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
using until_rec_c = jln::mp::if_<
  jln::mp::less_than_c<n>,
  jln::mp::inc<>,
  jln::mp::cfe<jln::mp::stop_iteration>
>;

template<
  template<class...> class Mp,
  template<class...> class Smp,
  class F,
  template<class...> class sfinae,
  int VerifySfinae = 1>
void test_rec()
{
  using namespace jln::mp;
  using namespace ut::ints;

  ut::same<_3, call<Mp<F>, _0>>();

  test_pack<Mp, identity>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  test_context<Mp<F>, Smp<sfinae<F>>, VerifySfinae>()
    .template test<_3, _0>()
    .template test<_3, _1>()
    .template test<_3, _2>()
    .template test<_3, _3>()
    .template test<_4, _4>()
    .template not_invocable<>()
    .template not_invocable<bad_number>()
    .template not_invocable<_0, _1>()
  ;
}

TEST()
{
  using namespace jln::mp;

  test_rec<recurse, smp::recurse, until_rec_c<3>, detail::sfinae>();
  test_rec<recurse_fix, smp::recurse_fix, until_rec_fix_c<3>, contract_barrier, -1>();
}

TEST_SUITE_END()
