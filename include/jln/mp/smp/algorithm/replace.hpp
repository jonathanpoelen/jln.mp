#pragma once

#include "remove.hpp"
#include "transform.hpp"
#include "../functional/if.hpp"
#include "../utility/always.hpp"
#include "../utility/same_as.hpp"
#include "../../algorithm/replace.hpp"

namespace jln::mp::smp
{
  template<class Pred, class T, class C = listify>
  using replace_if = detail::sfinae<mp::replace_if<
    subcontract_barrier<Pred>, T, subcontract_barrier<C>>>;

  template<class T, class U, class C = listify>
  using replace = contract<
    mp::replace<T, U, monadic_xs_if_na<U, subcontract<C>>>>;
}
