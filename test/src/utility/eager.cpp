#include "test.hpp"
#include "test/numbers.hpp"

#include "jln/mp/utility/eager.hpp"
#include "jln/mp/smp/list/size.hpp"

TEST_SUITE_BEGIN()

TEST()
{
  using namespace jln::mp;
  using namespace TU::ints;

  IS_SAME(_3, eager<seq_0_0_0, size<>>);
}

TEST_SUITE_END()
