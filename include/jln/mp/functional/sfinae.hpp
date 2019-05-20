#pragma once

#include "when.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<template<class> class sfinae, class x>
    struct _sfinae;

    template<class x> struct _recursive_sfinae_impl;
    template<class x> struct _sfinae_once_impl;
    template<class x> struct _recursive_unsafe_sfinae_impl;
    template<class x> struct _unsafe_sfinae_once_impl;

    template<class x>
    using _recursive_sfinae = typename _recursive_sfinae_impl<x>::type;

    template<class x>
    using _sfinae_once = typename _sfinae_once_impl<x>::type;

    template<class x>
    using _recursive_unsafe_sfinae = typename _recursive_unsafe_sfinae_impl<x>::type;

    template<class x>
    using _unsafe_sfinae_once = typename _unsafe_sfinae_once_impl<x>::type;
  }

  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  using sfinae_once = typename detail::_sfinae<detail::_sfinae_once, x>::type;

  template<class x>
  using unsafe_sfinae = typename detail::_sfinae<detail::_recursive_unsafe_sfinae, x>::type;

  template<class x>
  using unsafe_sfinae_once = typename detail::_sfinae<detail::_unsafe_sfinae_once, x>::type;
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
    using type = typename _sfinae<eager::identity, x>::type;
  };

  template<class x>
  struct _recursive_unsafe_sfinae_impl
  {
    using type = typename _sfinae<_recursive_unsafe_sfinae, x>::type;
  };

  template<class x>
  struct _unsafe_sfinae_once_impl
  {
    using type = typename _sfinae<eager::identity, x>::type;
  };
}
