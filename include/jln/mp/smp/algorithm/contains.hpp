#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/contains.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = contract<mp::any_of<mp::is<x>, assume_number<C>>>;
}
