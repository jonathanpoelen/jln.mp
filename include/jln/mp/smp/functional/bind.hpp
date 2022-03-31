#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/partial.hpp>
#include <jln/mp/functional/bind.hpp>

namespace jln::mp::smp
{
  template<class F, class C>
  using bind1st = partial<F, C>;

  template<class F, class C>
  using bind2nd = partial<identity, F, C>;
}
