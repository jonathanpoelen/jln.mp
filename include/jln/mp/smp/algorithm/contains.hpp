#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/algorithm/contains.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = contract<mp::drop_until<mp::is<x>, always<true_, C>, always<false_, C>>>;
}
