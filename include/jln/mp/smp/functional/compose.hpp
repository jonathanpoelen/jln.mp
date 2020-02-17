#pragma once

#include "../../functional/compose.hpp"
#include "../functional/identity.hpp"
#include "../functional/function.hpp"
#include "../functional/fork.hpp"

namespace jln::mp::smp
{
  template <template<class...> class F, template<class...> class... Fs>
  using compose = typename mp::detail::sfinae<
    mp::compose_f<mp::cfe<F>, mp::cfe<Fs>...>
  >;

  template<class F, class... Fs>
  using compose_f = typename mp::detail::sfinae<
    mp::compose_f<F, Fs...>
  >;
}
