#pragma once

#include "list.hpp"
#include "../error.hpp"
#include "../config/debug.hpp"
#include "../sfinae/sfinaefwd.hpp"
#include "../list/is_list.hpp"
#include "../algorithm/all_of.hpp"

#include <cstddef>


namespace jln::mp
{
  namespace detail
  {
    template<std::size_t n JLN_MP_DEBUG_A(class = err::all_parameters_must_be_of_type_mp_list)>
    struct _join_select;
  }

  template<class continuation = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>::template f<continuation::template f, seqs...>::type;
  };

  namespace eager
  {
    template<class... seqs>
    using join = typename mp::join<>::template f<seqs...>;
  }

  namespace smp
  {
    template<class continuation = listify>
    using join = when<all_of<is_list<>>, mp::join<when_continuation<continuation>>>;
  }
}

#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class continuation>
  struct _sfinae<sfinae, join<continuation>>
  {
    using type = smp::join<sfinae<continuation>>;
  };


  template<std::size_t n JLN_MP_DEBUG_A(class error)>
  struct _join_select : _join_select<(n <= 16 ? 16 : n <= 64 ? 64 : n <= 256 ? 256 : 1024)>
  {};

#define JLN_MP_JOIN_SELECT(n, mp_xs)                                         \
  template<JLN_MP_DEBUG(class error)>                                        \
  struct _join_select<n JLN_MP_DEBUG_A(error)>                               \
  {                                                                          \
    template<template<class...> class function, mp_xs(class, = list<>)>      \
    struct f;                                                                \
                                                                             \
    template<template<class...> class function, mp_xs(class..., JLN_MP_NIL)> \
    struct f<function, mp_xs(list<, ...>)>                                   \
    {                                                                        \
      using type = function<mp_xs(JLN_MP_NIL, ...)>;                         \
    };                                                                       \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_JOIN_SELECT)

#undef JLN_MP_JOIN_SELECT

  template<JLN_MP_DEBUG(class error)>
  struct _join_select<1024 JLN_MP_DEBUG_A(error)>
  {
    template<template<class...> class function, JLN_MP_XS_1024(class, = list<>), class... tail>
    struct f;

    template<template<class...> class function, JLN_MP_XS_1024(class..., JLN_MP_NIL), class... tail>
    struct f<function, JLN_MP_XS_1024(list<, ...>), tail...>
    : _join_select<sizeof...(tail)+1>::template f<function, list<JLN_MP_XS_1024(JLN_MP_NIL, ...)>, tail...>
    {};
  };
} // namespace jln::mp::detail
