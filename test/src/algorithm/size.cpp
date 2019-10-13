#include "test.hpp"

#include "jln/mp/list/size.hpp"

namespace
{
  TEST()
  {
    using namespace jln::mp;

    test_context<size<>, smp::size<>>()
      .test<number<0>>()
      .test<number<1>, int>()
      .test<number<2>, int, int>()
      ;
  }
}
