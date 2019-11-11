#pragma once

#include "remove_if.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/replace.hpp"

namespace jln::mp::smp
{
  template<class T, class U, class C = listify>
  using replace = valid_contract<
    mp::replace<T, U, monadic_xs_if_na<U, subcontract<C>>>>;
}
