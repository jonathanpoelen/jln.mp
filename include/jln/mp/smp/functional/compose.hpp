#pragma once

#include "../../functional/compose.hpp"
#include "../../functional/contract.hpp"
#include "../functional/identity.hpp"
#include "../functional/function.hpp"
#include "../functional/fork.hpp"

namespace jln::mp::smp
{
  template <template<class...> class F, template<class...> class... Fs>
  using compose_f = mp::detail::sfinae<
    mp::compose<mp::cfe<F>, mp::cfe<Fs>...>
  >;

  template<class F, class... Fs>
  using compose = mp::detail::sfinae<
    mp::compose<subcontract_barrier<F>, subcontract_barrier<Fs>...>
  >;
}
