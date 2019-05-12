#pragma once

#include "identity.hpp"
#include "call.hpp"
#include "../sfinae/when.hpp"


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
      if_<is_invocable<cfe<function>>, is_invocable<cfl<function>>, always<false_>>,
      cfl<function, continuation>>;

    template<template<class...> class function, class continuation = identity>
    using cfe = when<is_invocable<cfe<function>>, cfe<function, continuation>>;
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
