#pragma once

#include <jln/mp/list/list.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/detail/call_trace.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class seq>
    struct _as_list
    {};
  }
  /// \endcond

  /// \ingroup list

  /// Extracts type paramaters of a template class or union, then constructs a \list.
  /// \pre \c seq must be compatible with \typelist or \c detail::_as_list<seq>::type.
  /// \treturn \list
  template<class C = identity>
  struct as_list
  {
    template<class seq>
    using f = JLN_MP_CALL_TRACE(C, typename detail::_as_list<seq>::type);
  };

  namespace emp
  {
    template<class seq, class C = mp::identity>
    using as_list = typename as_list<C>::template f<seq>;
  }
}

#include <jln/mp/number/number.hpp>

/// \cond
namespace jln::mp
{
  template<>
  struct as_list<identity>
  {
    template<class seq>
    using f = typename detail::_as_list<seq>::type;
  };
}

namespace jln::mp::detail
{
  template<template<class...> class seq, class... xs>
  struct _as_list<seq<xs...>>
  {
    using type = list<xs...>;
  };

  template<template<class T, T...> class seq, class T, T... ns>
  struct _as_list<seq<T, ns...>>
  {
    using type = list<number<ns>...>;
  };

  template<template<auto...> class seq, auto... ns>
  struct _as_list<seq<ns...>>
  {
    using type = list<number<ns>...>;
  };
}
/// \endcond
