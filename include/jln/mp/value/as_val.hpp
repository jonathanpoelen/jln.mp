#pragma once

#include <jln/mp/functional/identity.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/value/val.hpp>

namespace jln::mp
{
  /// \ingroup value

  /// \cond
#ifdef _MSC_VER
  namespace detail
  {
    template<class x>
    struct _one
    {
      using type = x;
    };
  }
#endif
  /// \endcond

  /// Converts \c x to \val.
  /// \pre \c emp::has_value<x> == \c true
  /// \treturn \bool
  template<class C = identity>
  struct as_val
  {
#if __cplusplus >= 201703L
# ifndef _MSC_VER
    template<class x>
    using f = JLN_MP_DCALL(sizeof(C), C, val<x::value>);
# else
    template<class... xs>
    using f = typename detail::_memoizer_impl<C, list<
      typename detail::_one<val<xs::value>...>::type
    >>::type;
# endif
#else
# ifndef _MSC_VER
    template<class x>
    using f = JLN_MP_DCALL(sizeof(C), C, typed_value<decltype(x::value), x::value>);
# else
    template<class... xs>
    using f = typename detail::_memoizer_impl<C, list<
      typename detail::_one<typed_value<decltype(x::value), x::value>...>::type
    >>::type;
# endif
#endif
  };

  /// \cond
  template<>
  struct as_val<identity>
  {
#if __cplusplus >= 201703L
# ifndef _MSC_VER
    template<class x>
    using f = val<x::value>;
# else
    template<class... xs>
    using f = typename detail::_one<val<xs::value>...>::type;
# endif
#else
# ifndef _MSC_VER
    template<class x>
    using f = typed_value<decltype(x::value), x::value>;
# else
    template<class... xs>
    using f = typename detail::_one<typed_value<decltype(xs::value), xs::value>...>::type;
# endif
#endif
  };
  /// \endcond

  namespace emp
  {
    template<class x, class C = mp::identity>
    using as_val = typename mp::as_val<C>::template f<x>;
  }
}
