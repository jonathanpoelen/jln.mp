#pragma once

#include "list.hpp"
#include "../error.hpp"
#include "../config/debug.hpp"

namespace jln::mp
{
  template<class continuation = listify>
  struct as_list;

  namespace detail
  {
    template<template<class...> class, class seq>
    struct _as_list JLN_MP_WITH_DEBUG(: error_occurred<as_list, err::you_need_to_add_a_specialization<seq>> {});
  }

  template<class continuation>
  struct as_list
  {
    template<class seq>
    using f = typename detail::_as_list<continuation::template f, seq>::type;
  };

  namespace emp
  {
    template<class seq, class continuation = listify>
    using as_list = typename detail::_as_list<continuation::template f, seq>::type;
  }
}

#include "../number/number.hpp"

namespace jln::mp::detail
{
  template<template<class...> class f, template<class...> class seq, class... xs>
  struct _as_list<f, seq<xs...>>
  {
    using type = f<xs...>;
  };

  template<template<class...> class f, template<class T, T...> class seq, class T, T... ns>
  struct _as_list<f, seq<T, ns...>>
  {
    using type = f<number<ns>...>;
  };

  template<template<class...> class f, template<auto...> class seq, auto... ns>
  struct _as_list<f, seq<ns...>>
  {
    using type = f<number<ns>...>;
  };
}
