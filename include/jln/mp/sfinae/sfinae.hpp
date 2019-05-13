#pragma once

#include "../functional/always.hpp"
#include "../functional/conditional.hpp"
#include "../number/number.hpp"
#include "sfinaefwd.hpp"

namespace jln::mp
{
  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  // TODO has_type or extract_type<..., identity, always<x>>
  using unsafe_sfinae = typename detail::_unsafe_sfinae<detail::_recursive_sfinae, x>::type;

  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  template<class function>
  using sfinae_barrier = when<always<true_>, function>;

  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  template<class predicate, class continuation>
  struct when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>
      ::template f<>;
  };
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, when<xs...>>
  {
    using type = when<xs...>;
  };

  template<template<class> class sfinae>
  struct _sfinae<sfinae, listify>
  {
    using type = listify;
  };

  template<class x>
  struct _recursive_sfinae_impl
  {
    using type = typename _sfinae<_recursive_sfinae, x>::type;
  };

  template<class predicate, class continuation>
  struct _when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>;
  };

  template<class function>
  struct _when_impl
  {
    template<class... xs>
    using f = always<typename function::template f<xs...>>;
  };

  template<class function>
  struct _when_continuation
  {
    using type = if_<is_invocable<function>, _when_impl<function>, unsatisfactory_concept>;
  };

  template<class predicate, class continuation>
  struct _when_continuation<when<predicate, continuation>>
  {
    using type = _when<predicate, continuation>;
  };

  template<>
  struct _when_continuation<listify>
  {
    using type = _when_impl<listify>;
  };

  template<class continuation>
  struct _when_continuation<when<always<true_>, continuation>>
  {
    using type = continuation;
  };

  template<template<class> class sfinae, class function, class>
  struct _unsafe_sfinae
  {
    using type = when<is_invocable<function>, function>;
  };

  template<template<class> class sfinae, class x>
  struct _unsafe_sfinae<sfinae, x, std::void_t<typename _sfinae<sfinae, x>::type>>
  : _sfinae<sfinae, x>
  {};
} // namespace jln::mp
