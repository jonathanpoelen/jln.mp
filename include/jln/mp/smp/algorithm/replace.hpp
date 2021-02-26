#pragma once

#include "remove.hpp"
#include "transform.hpp"
#include "../functional/if.hpp"
#include "../utility/always.hpp"
#include "../utility/is.hpp"
#include "../../algorithm/replace.hpp"

namespace jln::mp::smp
{
  template<class Pred, class T, class C = listify>
  using replace_if = detail::sfinae<mp::replace_if<
    assume_unary_barrier<Pred>, T, subcontract_barrier<C>>>;

  template<class T, class U, class C = listify>
  using replace = contract<
    mp::replace<T, U, monadic_if_na<U, monadic_xs, subcontract<C>>>>;
}
