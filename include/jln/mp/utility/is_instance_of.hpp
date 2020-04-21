#pragma once

#include "../number/number.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class Tpl, class T>
    struct _is_instance_of;
  }
  /// \endcond

  /// \ingroup trait

  /// \return \boolean
  template<template<class...> class Tpl, class C = identity>
  struct is_instance_of
  {
    template<class x>
    using f = typename C::template f<
      typename detail::_is_instance_of<Tpl, x>::type>;
  };

  namespace emp
  {
    template<template<class...> class Tpl, typename x>
    using is_instance_of = typename detail::_is_instance_of<Tpl, x>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class T>
  struct _is_instance_of
  {
    using type = false_;
  };

  template<template<class...> class Tpl, class... Ts>
  struct _is_instance_of<Tpl, Tpl<Ts...>>
  {
    using type = true_;
  };
}
/// \endcond
