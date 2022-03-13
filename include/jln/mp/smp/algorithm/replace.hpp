#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/replace.hpp>

namespace jln::mp::smp
{
  template<class Pred, class T, class C = listify>
  using replace_if = detail::sfinae<mp::replace_if<
    assume_unary_barrier<Pred>, T, subcontract_barrier<C>>>;

  template<class T, class U, class C = listify>
  using replace = contract<
    mp::replace<T, U, monadic_if_na<U, monadic_xs, subcontract<C>>>>;
}
