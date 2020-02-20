#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/fork_front.hpp"
#include "jln/mp/smp/functional/function.hpp"
#include "jln/mp/smp/list/pop_front.hpp"
#include "jln/mp/smp/list/front.hpp"
#include "jln/mp/smp/list/take.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class, class, class, class>
  using f = int;
};

struct S { static constexpr const char* value = ""; };

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  test_pack<fork, always<listify>>()
    .test_variadic()
    .test_binary()
    .test_unary()
  ;

  ut::same<list<void, int>, fork_front<front<cfe<take, cfe<pop_front>>>>
    ::template f<_2, void, int, char, long>>();

  test_context<
    fork_front<front<cfe<take, cfe<pop_front>>>>,
    smp::fork_front<smp::front<smp::cfe<smp::take, smp::cfe<smp::pop_front>>>>,
    -1
  >()
    .test<list<void, int>, _2, void, int, char, long>()
    .not_invocable<void, void, int, char, long>()
    .not_invocable<_5, void, int, char, long>()
    ;
}

TEST_SUITE_END()
