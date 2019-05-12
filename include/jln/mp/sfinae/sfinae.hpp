#pragma once

#include "list.hpp"
#include "../error.hpp"
#include "../config/debug.hpp"

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
  } // namespace eager
}

#include "../functional/always.hpp"
#include "../functional/if.hpp"

namespace jln::mp
{
  namespace smp
  {
    struct unsatisfactory_concept_error;
    using unsatisfactory_concept = always<unsatisfactory_concept_error>;

    template<class predicate, template<class...> class function, class continuation>
    struct when;

    // TODO if_<is_invocable<function>, fork<function, cfe<always>>, unsatisfactory_concept>
    template<class function>
    struct _when_impl
    {
      template<class... xs>
      using f = always<typename function::template f<xs...>>;
    };

    template<class predicate, template<class...> class function, class continuation>
    struct _when
    {
      template<class... xs>
      using f = typename mp::conditional_c<predicate::template f<xs...>::value>
        ::template f<
          if_<is_invocable<function<continuation>>, _when_impl<function<continuation>>, unsatisfactory_concept>,
          unsatisfactory_concept>
        ::template f<xs...>;
    };

    template<
      class predicate, template<class...> class function,
      class subpredicate, template<class...> class subfunction, class continuation>
    struct _when<predicate, function, when<subpredicate, subfunction, continuation>>
    {
      template<class... xs>
      using f = typename mp::conditional_c<predicate::template f<xs...>::value>
        ::template f<function<_when<subpredicate, subfunction, continuation>>, unsatisfactory_concept>
        ::template f<xs...>;
    };

    template<class predicate, template<class...> class function, class continuation>
    struct when
    {
      template<class... xs>
      using f = typename _when<predicate, function, continuation>
        ::template f<xs...>
        ::template f<>;
    };

    template<class predicate, class continuation = identity>
    struct all_of
    {
      template<class... xs>
      using f = typename continuation::template f<number<(predicate::template f<xs>::value && ... && true)>>;
    };

    namespace traits
    {
      template<class x> struct is_list{ using type = false_; };
      template<class... xs> struct is_list<list<xs...>> { using type = true_; };
    }

    template<class continuation = identity>
    struct is_list
    {
      template<class x>
      using f = typename continuation::template f<typename traits::is_list<x>::type>;
    };

    template<class continuation = listify>
    using join = when<all_of<is_list<>>, mp::join, continuation>;
  }
}


#include "../config/enumerate.hpp"

namespace jln::mp::detail
{
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
} // namespace jln::mp
