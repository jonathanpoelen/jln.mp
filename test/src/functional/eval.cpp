#include "test/test_case.hpp"

#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L

#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/smp/functional/eval.hpp"
#include "jln/mp/smp/list/push_front.hpp"
#include "jln/mp/smp/list/listify.hpp"

TEST_SUITE_BEGIN()

struct foo
{
  template<class T>
  T operator()() const
  {
    return T{};
  }
};

constexpr struct { } noop {};

TEST()
{
  using namespace jln::mp;
  using namespace ut::ints;

  (void)eval<noop, ut::unary>();
  (void)eval<noop, ut::binary>();
  (void)eval<noop, ut::listify>();
  (void)eval<noop, ut::variadic>();

  ut::not_invocable<eval<noop>, int>();

  constexpr foo f;

  ut::same<int, emp::eval<f, int>>();

  test_context<eval<f>, smp::eval<f>>()
    .test<int, int>()
    .not_invocable<>()
    .not_invocable<int, int>()
    ;

  ut::not_invocable<smp::eval<bad_function>>();
}

TEST_SUITE_END()
#endif
#endif
