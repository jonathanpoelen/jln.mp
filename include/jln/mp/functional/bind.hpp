#pragma once

#include "identity.hpp"
#include "../number/number.hpp"
#include "call.hpp"


namespace jln::mp
{
  template<template<class...> class function, class continuation = identity>
  struct cfl
  {
    template<class... xs>
    using f = call<continuation, typename function<xs...>::type>;
  };

  // TODO using cfe = cfl<function, cfl<get_type, continuation>>
  // TODO using cfe = cfl<function, get_type<continuation>>
  template<template<class...> class function, class continuation = identity>
  struct cfe
  {
    template<class... xs>
    using f = call<continuation, function<xs...>>;
  };

  template<template<auto...> class function, class continuation = identity>
  struct vcfl
  {
    template<int_... ns>
    using f = call<continuation, typename function<ns...>::type>;
  };

  template<template<auto...> class function, class continuation = identity>
  struct vcfe
  {
    template<int... ns>
    using f = call<continuation, function<ns...>>;
  };
}
