#pragma once

#include "list.hpp"
#include "../functional/identity.hpp"
#include "../number/numbers.hpp"
#include "../number/is_number.hpp"

#include <utility>


#ifndef JLN_MP_HAS_MAKE_INTEGER_SEQ
# if defined(__has_builtin)
#   if __has_builtin(__make_integer_seq)
#     define JLN_MP_HAS_MAKE_INTEGER_SEQ 1
#   else
#     define JLN_MP_HAS_MAKE_INTEGER_SEQ 0
#   endif
# else
#   define JLN_MP_HAS_MAKE_INTEGER_SEQ 0
# endif
#endif

namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _enumerate;

#if JLN_MP_HAS_MAKE_INTEGER_SEQ
    template<int_ n, class continuation>
    using _enumerate_v_c = __make_integer_seq<
      detail::_enumerate<continuation>::template f, int_, n>;
#else
    template<int_ n, class continuation>
    using _enumerate_v_c = typename detail::_enumerate<
      std::make_index_sequence<n>>::template f<continuation>;
#endif
  }

  template<class continuation = listify>
  struct enumerate
  {
    template<class n>
    using f = detail::_enumerate_v_c<n::value, numbers<continuation>>;
  };

  namespace eager
  {
    template<int_ n, class continuation = listify>
    using enumerate_c = detail::_enumerate_v_c<n, mp::numbers<continuation>>;

    template<class n, class continuation = listify>
    using enumerate = detail::_enumerate_v_c<n::value, mp::numbers<continuation>>;
  }

  namespace smp
  {
    template<class continuation = listify>
    using enumerate = when<mp::is_number<>, mp::enumerate<when_continuation<continuation>>>;
  }
}

namespace jln::mp::detail
{
  template<template<class> class sfinae, class continuation>
  struct _sfinae<sfinae, enumerate<continuation>>
  {
    using type = smp::enumerate<sfinae<continuation>>;
  };

#if JLN_MP_HAS_MAKE_INTEGER_SEQ
  template<class continuation>
  struct _enumerate
  {
    template<class, int_... ns>
    using f = typename continuation::template f<ns...>;
  };
#else
  template<std::size_t... ns>
  struct _enumerate<std::integer_sequence<std::size_t, ns...>>
  {
    template<class continuation>
    using f = typename continuation::template f<ns...>;
  };
#endif
}

#if 0
namespace jln::mp::detail
{
  template<int_...>
  class enumeration;

  template<bool, int_ n, class ns1>
  struct _enumerate_impl;

  template<int_ n, int_... ns1>
  struct _enumerate_impl<false, n, enumeration<ns1...>>
  {
    using type = enumeration<ns1..., (n+ns1)...>;
  };

  template<int_ n, int_... ns1>
  struct _enumerate_impl<true, n, enumeration<ns1...>>
  {
    using type = enumeration<ns1..., (n+ns1)..., n*2+1>;
  };

  template<int_ n>
  struct _enumerate
 : _enumerate_impl<bool(n & 1), n/2, typename _enumerate<n / 2>::type>
  {};

  template<>
  struct _enumerate<0>
  {
    using type = enumeration<>;
  };
}
#endif
