#pragma once

namespace jln::mp
{
  namespace detail
  {
    template<template<class> class sfinae, class x>
    struct _sfinae;

    template<template<class> class sfinae, class x, class = void>
    struct _unsafe_sfinae;

    template<class x>
    struct _recursive_sfinae_impl;

    template<class x>
    using _recursive_sfinae = typename _recursive_sfinae_impl<x>::type;
  }

  template<class x>
  using sfinae = typename detail::_sfinae<detail::_recursive_sfinae, x>::type;

  template<class x>
  // TODO has_type or extract_type<..., identity, always<x>>
  using unsafe_sfinae = typename detail::_unsafe_sfinae<detail::_recursive_sfinae, x>::type;
}


#include <type_traits>

namespace jln::mp::detail
{
  template<class x>
  struct _recursive_sfinae_impl
  {
    using type = typename _unsafe_sfinae<_recursive_sfinae, x>::type;
  };

  template<template<class> class sfinae, class x, class>
  struct _unsafe_sfinae
  {
    using type = x;
  };

  template<template<class> class sfinae, class x>
  struct _unsafe_sfinae<sfinae, x, std::void_t<typename _sfinae<sfinae, x>::type>>
 : _sfinae<sfinae, x>
  {};
} // namespace jln::mp
