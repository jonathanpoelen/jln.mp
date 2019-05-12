#pragma once

#include "../functional/always.hpp"
#include "../functional/if.hpp"

namespace jln::mp
{
  struct unsatisfactory_concept_error;
  using unsatisfactory_concept = always<unsatisfactory_concept_error>;

  namespace detail
  {
    template<class continuation>
    struct _when_continuation;
  }

  template<class predicate, class continuation>
  struct when
  {
    template<class... xs>
    using f = typename mp::conditional_c<predicate::template f<xs...>::value>
      ::template f<continuation, unsatisfactory_concept>
      ::template f<xs...>
      ::template f<>;
  };

  template<class continuation>
  using when_continuation = typename detail::_when_continuation<continuation>::type;
}


#include "sfinae.hpp"

namespace jln::mp::detail
{
  template<template<class> class sfinae, class... xs>
  struct _sfinae<sfinae, when<xs...>>
  {
    using type = when<xs...>;
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

  template<class continuation>
  struct _when_continuation<when<always<true_>, continuation>>
  {
    using type = continuation;
  };
}
