#pragma once

#include "../functional/when.hpp"
#include "../list/size.hpp"
#include "../utility/same_as.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_number;
  }

  namespace emp
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }

  template<class continuation = identity>
  struct is_number
  {
    template<class x>
    using f = call<continuation, typename detail::_is_number<x>::type>;
  };

  namespace smp
  {
    template<class continuation = identity>
    using is_number = when<
      mp::size_of_1<>,
      // TODO when_continuation_or_identity
      // when<mp::size_of_1<>, C> -> C
      // when<mp::alway<true_>, identity> -> identity
      // identity -> identity
      mp::is_number<when_continuation<continuation>>>;
  }
}

#include "number.hpp"

namespace jln::mp::detail
{
  template<class x>
  struct _is_number
  {
    using type = false_;
  };

  template<int_ x>
  struct _is_number<number<x>>
  {
    using type = true_;
  };

  template<template<class> class sfinae, class continuation>
  struct _sfinae<sfinae, is_number<continuation>>
  {
    using type = smp::is_number<sfinae<continuation>>;
  };
}
