#pragma once

#include "../contract.hpp"
#include "../../functional/compose.hpp"
#include "../functional/identity.hpp"
#include "../functional/lift.hpp"
#include "../functional/tee.hpp"

namespace jln::mp::smp
{
  template <template<class...> class F, template<class...> class... Fs>
  using compose_f = mp::detail::sfinae<
    mp::compose<mp::lift<F>, mp::lift<Fs>...>
  >;

  template<class F, class... Fs>
  using compose = mp::detail::sfinae<
    mp::compose<subcontract_barrier<F>, subcontract_barrier<Fs>...>
  >;
}
