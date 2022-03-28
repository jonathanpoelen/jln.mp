#pragma once

#include <jln/mp/smp/algorithm/find.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/smp/functional/recursively.hpp>
#include <jln/mp/algorithm/find_last.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if = find_if<Pred, recursively<
    pop_front<find_if<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<class Pred, class TC = listify, class FC = clear<TC>>
  using find_last_if_not = find_if_not<Pred, recursively<
    pop_front<find_if_not<Pred, next_recursion, stop_recursion>>,
    TC
  >, FC>;

  template<class T, class TC = listify, class FC = clear<TC>>
  using find_last = contract<mp::find_last<T, subcontract<TC>, subcontract<FC>>>;
}
