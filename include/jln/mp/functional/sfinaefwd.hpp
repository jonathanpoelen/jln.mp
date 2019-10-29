#pragma once

#include "identity.hpp"

// TODO include smp/* ?

// TODO mp::unsafe_sfinae / mp::unsafe_sfinae_once ? for sfinae<F> without specialization on F
namespace jln::mp
{
  namespace detail
  {
    template<template<class> class sfinae, class x>
    struct _sfinae;

    template<class x> struct _recursive_sfinae_impl;
    template<class x> struct _sfinae_once_impl;

    template<class x>
    using _recursive_sfinae = typename _recursive_sfinae_impl<x>::type;

    template<class x>
    using _sfinae_once = typename _sfinae_once_impl<x>::type;
  }
}


namespace jln::mp::detail
{
  template<class x>
  struct _recursive_sfinae_impl
  {
    using type = typename _sfinae<_recursive_sfinae, x>::type;
  };

  template<class x>
  struct _sfinae_once_impl
  {
    using type = typename _sfinae<emp::identity, x>::type;
  };
}
