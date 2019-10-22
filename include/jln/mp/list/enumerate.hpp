#pragma once

#include "list.hpp"
#include "../functional/identity.hpp"
#include "../number/numbers.hpp"
#include "../number/is_number.hpp"

#include <utility>


#if defined(__has_builtin)
#  if __has_builtin(__make_integer_seq)
#    define JLN_MP_USE_INTEGER_PACK 0
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#  elif __has_builtin(__integer_pack)
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#elif defined(__GNUC__)
#  if __GNUC__ >= 8
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#else
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#endif

#include "../number/numbers.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _enumerate;
  }

  // TODO enumerate -> make_int_sequence
  // TODO enumerate is zip<make_int_sequence, list>
  template<class C = numbers<>>
  struct enumerate_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    using f = typename detail::_enumerate<n>::type::template f<C>;
#else
    using f = typename detail::_enumerate<
      std::make_index_sequence<n::value>>::template f<C>;
#endif
  };

  template<class C = mp::listify>
  struct enumerate : enumerate_v<mp::numbers<C>>
  {};

  namespace emp
  {
    template<class n, class C = mp::numbers<>>
    using enumerate_v = typename mp::enumerate_v<C>::template f<n>;

    template<int_ n, class C = mp::numbers<>>
    using enumerate_v_c = enumerate_v<mp::number<n>, C>;

    template<class n, class C = mp::listify>
    using enumerate = typename mp::enumerate<C>::template f<n>;

    template<int_ n, class C = mp::listify>
    using enumerate_c = enumerate<mp::number<n>, C>;
  }

  namespace smp
  {
    template<class C = listify>
    using enumerate = when<mp::is_number<>, mp::enumerate<when_continuation<C>>>;
  }
} // namespace jln::mp

namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, enumerate<C>>
  {
    using type = smp::enumerate<sfinae<C>>;
  };

#if JLN_MP_USE_MAKE_INTEGER_SEQ
  template<class, int_... ns>
  struct _enumerate_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<class n>
  struct _enumerate
  {
    using type = __make_integer_seq<_enumerate_impl, int_, n::value>;
  };
#elif JLN_MP_USE_INTEGER_PACK
  template<int_... ns>
  struct _enumerate_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<class n>
  struct _enumerate
  {
    using type = _enumerate_impl<__integer_pack(n::value)...>;
  };
#else
  template<std::size_t... ns>
  struct _enumerate<std::integer_sequence<std::size_t, ns...>>
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };
#endif
}

#undef JLN_MP_USE_INTEGER_PACK
#undef JLN_MP_USE_MAKE_INTEGER_SEQ

#if 0
namespace jln::mp::emp
{
  template<int_ n, class C = listify>
  using enumerate_c = typename _enumerate<
    (n == 0 ? 0 : n == 1 ? -1 : n-1)
  >::template f<jln::mp::numbers<C>>;
}

namespace jln::mp::detail
{
  template<int_...>
  class enumeration;

  template<bool, int_ n, class ns>
  struct _enumerate_impl;

  template<int_ n, int_... ns>
  struct _enumerate_impl<false, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)...>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)...>;
  };

  template<int_ n, int_... ns>
  struct _enumerate_impl<true, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)..., n*2+1>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)..., n*2+1>;
  };

  template<int_ n>
  struct _enumerate
 : _enumerate_impl<bool(n & 1), n/2, typename _enumerate<n / 2>::type>
  {};

  template<>
  struct _enumerate<0>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _enumerate<-1>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<0>;
  };
}
#endif
