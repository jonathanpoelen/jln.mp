#pragma once

#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<template<class...> class Tpl, class T>
    struct _is_specialization_of;
  }
  /// \endcond

  /// \ingroup trait

  /// Checks whether \c x is \c Tpl<xs...>
  /// \treturn \bool
  template<template<class...> class Tpl, class C = identity>
  struct is_specialization_of
  {
    template<class x>
    using f = JLN_MP_CALL_TRACE(C,
      typename detail::_is_specialization_of<Tpl, x>::type);
  };

  namespace emp
  {
    template<template<class...> class Tpl, class x>
    using is_specialization_of = typename detail::_is_specialization_of<Tpl, x>::type;
  }
}

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class T>
  struct _is_specialization_of
  {
    using type = false_;
  };

  template<template<class...> class Tpl, class... Ts>
  struct _is_specialization_of<Tpl, Tpl<Ts...>>
  {
    using type = true_;
  };
}
/// \endcond
