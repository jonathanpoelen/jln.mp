#include "test.hpp"

#include "jln/mp/functional/call.hpp"
#include "jln/mp/functional/bind.hpp"

namespace
{
  namespace bind_test
  {
    template<class x>
    using eager = x;

    template<class x>
    struct lazy
    {
      using type = x;
    };
  }

  TEST()
  {
    using namespace jln::mp;
    namespace t = bind_test;

    class x{};

    test_context<cfe<t::eager>, smp::cfe<t::eager>>()
      .test<x, x>()
      ;
    test_context<cfl<t::lazy>, smp::cfl<t::lazy>>()
      .test<x, x>()
      ;
    test_context<cfe<t::lazy>, smp::cfe<t::lazy>>()
      .test<t::lazy<x>, x>()
      ;
  }
}
