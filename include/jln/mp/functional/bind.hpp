#pragma once

#include "identity.hpp"
#include "call.hpp"
#include "../sfinae/sfinaefwd.hpp"
#include "../functional/always.hpp"
#include "../functional/if.hpp"
#include "../functional/is_invovable.hpp"


namespace jln::mp
{
  template<template<class...> class function, class continuation = identity>
  struct cfl
  {
    template<class... xs>
    using f = call<continuation, typename function<xs...>::type>;
  };

  template<template<class...> class function, class continuation = identity>
  struct cfe
  {
    template<class... xs>
    using f = call<continuation, function<xs...>>;
  };

  namespace smp
  {
    template<template<class...> class function, class continuation = identity>
    using cfl = when<
      mp::if_<mp::is_invocable<mp::cfe<function>>, mp::is_invocable<mp::cfl<function>>, mp::always<false_>>,
      mp::cfl<function, continuation>>;

    template<template<class...> class function, class continuation = identity>
    using cfe = when<mp::is_invocable<mp::cfe<function>>, mp::cfe<function, continuation>>;
  }
}


namespace jln::mp::detail
{
  template<template<class> class sfinae, template<class...> class function, class continuation>
  struct _sfinae<sfinae, cfl<function, continuation>>
  {
    using type = smp::cfl<function, sfinae<continuation>>;
  };

  template<template<class> class sfinae, template<class...> class function, class continuation>
  struct _sfinae<sfinae, cfe<function, continuation>>
  {
    using type = smp::cfe<function, sfinae<continuation>>;
  };
}
