/* The MIT License (MIT)

Copyright (c) 2019 jonathan poelen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <type_traits>
#include <type_traits>
#include <algorithm>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <type_traits>
#include <type_traits>
#include <type_traits>
#include <type_traits>
#include <algorithm>
#include <type_traits>
#include <type_traits>
#include <type_traits>

namespace jln::mp
{
  struct identity
  {
    template<class x>
    using f = x;
  };

  namespace emp
  {
    template<class x>
    using identity = x;
  }
} // namespace jln::mp
namespace jln::mp
{
  namespace detail
  {
    template <class L> struct _unpack;
    template <class L> struct _unpack_append;
  }

  template<class C>
  struct unpack
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack<seq>::template f<C, xs...>;
  };

  template<class C>
  struct unpack_append
  {
    template<class seq, class... xs>
    using f = typename detail::_unpack_append<seq>::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C, class... xs>
    using unpack = typename detail::_unpack<L>::template f<C, xs...>;

    template<class L, class C, class... xs>
    using unpack_append = typename detail::_unpack_append<L>::template f<C, xs...>;
  }
} // namespace jln::mp


#ifndef JLN_MP_ENABLE_DEBUG
#  define JLN_MP_ENABLE_DEBUG 0
#endif

#if JLN_MP_ENABLE_DEBUG
#  define JLN_MP_DEBUG_A(...) , __VA_ARGS__
#  define JLN_MP_DEBUG_B(...) __VA_ARGS__,
#  define JLN_MP_DEBUG(...) __VA_ARGS__
#else
#  define JLN_MP_DEBUG_A(...)
#  define JLN_MP_DEBUG_B(...)
#  define JLN_MP_DEBUG(...)
#endif
namespace jln::mp
{
  namespace detail
  {
    template<bool> struct dcall;
    template<bool> struct dcallf;
    template<bool> struct dcall_c;
    template<bool> struct dcall_v;
#if __cplusplus >= 201703L
    template<bool> struct dcallf_c;
    template<bool> struct dcallf_tc;
#endif

    template<class F, class... xs>
    struct _memoizer;
  }

  template<class C, class... xs>
  using memoize_call = typename detail::_memoizer<C, xs...>::type;

#if JLN_MP_ENABLE_DEBUG
  template<class C, class... xs>
  using call = typename detail::_memoizer<C, xs...>::type;

  template<class C, class F, class... xs>
  using dispatch = typename detail::_memoizer<C,
    typename detail::_memoizer<F, xs>::type...
  >::type;

  template<class F, class C, class... xs>
  using indirect_call = typename detail::_memoizer<
    typename detail::_memoizer<F, xs...>::type,
    C, xs...
  >::type;

  template<class C, class F, class... xs>
  using unary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F, xs...>::type
  >::type;

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F0, xs...>::type,
    typename detail::_memoizer<F1, xs...>::type
  >::type;

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = typename detail::_memoizer<C,
    typename detail::_memoizer<F0, xs...>::type,
    typename detail::_memoizer<F1, xs...>::type,
    typename detail::_memoizer<F2, xs...>::type
  >::type;
#else
  template<class C, class... xs>
  using call = typename detail::dcall<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;

  template<class C, class... xs>
  using call_v = typename detail::dcall_v<(sizeof...(xs) < 1000000)>
    ::template f<C, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _indirect_call = f<f<F, xs...>, C, xs...>;
  }

  template<class F, class C, class... xs>
  using indirect_call = detail::_indirect_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _dispatch = f<C, f<F, xs>...>;
  }

  template<class C, class F, class... xs>
  using dispatch = detail::_dispatch<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F, class... xs>
    using _unary_compose_call = f<C, f<F, xs...>>;
  }

  template<class C, class F, class... xs>
  using unary_compose_call = detail::_unary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F0, class F1, class... xs>
    using _binary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>>;
  }

  template<class C, class F0, class F1, class... xs>
  using binary_compose_call = detail::_binary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F0, F1, xs...>;

  namespace detail
  {
    template<template<class...> class f, class C, class F0, class F1, class F2, class... xs>
    using _ternary_compose_call = f<C, f<F0, xs...>, f<F1, xs...>, f<F2, xs...>>;
  }

  template<class C, class F0, class F1, class F2, class... xs>
  using ternary_compose_call = detail::_ternary_compose_call<
    detail::dcall<(sizeof...(xs) < 1000000)>::template f,
    C, F0, F1, F2, xs...>;
#endif
}

namespace jln::mp::detail
{
  template<class F, class... xs>
  struct _memoizer
  {
    using type = typename F::template f<xs...>;
  };

  template<>
  struct dcall<true>
  {
      template<class C, typename...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcall_v<true>
  {
      template<class C, class...xs>
      using f = typename C::template f<xs::value...>;
  };

  template<>
  struct dcall_c<true>
  {
      template<class C, auto...xs>
      using f = typename C::template f<xs...>;
  };

  template<>
  struct dcallf<true>
  {
    template<template<class...> class F, class...xs>
    using f = F<xs...>;
  };

#if __cplusplus >= 201703L
  template<>
  struct dcallf_c<true>
  {
    template<template<auto...> class F, auto...vs>
    using f = F<vs...>;
  };

  template<>
  struct dcallf_tc<true>
  {
    template<template<class, auto...> class F, class x, auto...vs>
    using f = F<x, vs...>;
  };
#endif
}
namespace jln::mp
{
  template<template<class...> class F, class C = identity>
  struct cfl
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type
    >;
  };

  template<template<class...> class F>
  struct cfl<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>::type;
  };

  template<template<class...> class F, class C = identity>
  struct cfe
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>
    >;
  };

  template<template<class...> class F>
  struct cfe<F, identity>
  {
    template<class... xs>
    using f = typename detail::dcallf<sizeof...(xs) < 1000000>
      ::template f<F, xs...>;
  };

#if __cplusplus >= 201703L
  template<template<auto...> class F>
  struct cfe_v
  {
    template<class... xs>
    using f = typename detail::dcallf_c<(sizeof...(xs) < 1000000)>
      ::template f<F, xs::value...>;
  };

  template<template<auto...> class F>
  struct cfe_c
  {
    template<auto... xs>
    using f = typename detail::dcallf_c<(sizeof...(xs) < 1000000)>
      ::template f<F, xs...>;
  };

  template<template<class, auto...> class F>
  struct cfe_tv
  {
    template<class x, class... xs>
    using f = typename detail::dcallf_tc<(sizeof...(xs) < 1000000)>
      ::template f<F, x, xs::value...>;
  };

  template<template<class, auto...> class F>
  struct cfe_tc
  {
    template<class x, auto... xs>
    using f = typename detail::dcallf_tc<(sizeof...(xs) < 1000000)>
      ::template f<F, x, xs...>;
  };
#endif
} // namespace jln::mp
namespace jln::mp
{
  template<class... xs>
  class list {};

  using listify = cfe<list>;

  template<>
  struct cfe<list, identity>
  {
    template<class... xs>
    using f = list<xs...>;
  };
} // namespace jln::mp
namespace jln::mp::detail
{
  template<template<class...> class Seq, class... ys>
  struct _unpack<Seq<ys...>>
  {
    template<class C, class... xs>
    using f = typename C::template f<xs..., ys...>;
  };

  template<template<class...> class Seq, class... xs>
  struct _unpack_append<Seq<xs...>>
  {
    template<class C, class... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class C>
  struct optimize_useless_unpack
  {
    using type = C;
  };

  template<>
  struct optimize_useless_unpack<unpack<listify>>
  {
    using type = identity;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<listify>>
  {
    using type = identity;
  };

  template<class C>
  using optimize_useless_unpack_t = typename optimize_useless_unpack<C>::type;
}
namespace jln::mp
{
  template<class T, class C = listify>
  struct push_front
  {
    template<class... xs>
    using f = call<C, T, xs...>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_front = unpack<L, mp::push_front<T, C>>;
  }
}
namespace jln::mp::detail
{
  constexpr unsigned min(unsigned a, unsigned b)
  {
    return a < b ? a : b;
  }

  constexpr unsigned max(unsigned a, unsigned b)
  {
    return a < b ? b : a;
  }

  constexpr unsigned n_8_or_less_16_64_256(unsigned n)
  {
    return
      n <= 8 ? n
    : n < 16 ? 8
    : n < 64 ? 16
    : n < 256 ? 64
    : 256
    ;
  }

  constexpr unsigned n_8_or_less_16_64(unsigned n)
  {
    return
      n <= 8 ? n
    : n < 16 ? 8
    : n < 64 ? 16
    : 64
    ;
  }

  constexpr unsigned n_4_or_less_8_16_64_256(unsigned n)
  {
    return
      n >= 256 ? 256
    : n >= 64 ? 64
    : n >= 16 ? 16
    : n >= 8 ? 8
    : n >= 4 ? 4
    : n
    ;
  }

  constexpr unsigned n_16_64_256_1024(unsigned n)
  {
    return
      n <= 16 ? 16
    : n <= 64 ? 64
    : n <= 256 ? 256
    : 1024
    ;
  }
}

#define JLN_MP_NIL
#define JLN_MP_COMMA ,
#define JLN_MP_PAREN_OPEN (
#define JLN_MP_PAREN_CLOSE )

#define JLN_MP_GEN_XS_16_64_256_1024(func)                       \
  func(16,   JLN_MP_XS_16,   JLN_MP_RXS_16,   JLN_MP_REPEAT_16)  \
  func(64,   JLN_MP_XS_64,   JLN_MP_RXS_64,   JLN_MP_REPEAT_64)  \
  func(256,  JLN_MP_XS_256,  JLN_MP_RXS_256,  JLN_MP_REPEAT_256) \
  func(1024, JLN_MP_XS_1024, JLN_MP_RXS_1024, JLN_MP_REPEAT_1024)

#define JLN_MP_GEN_XS_8(func)                               \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8) \

#define JLN_MP_GEN_XS_8_args(func, ...) \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8, __VA_ARGS__)

#define JLN_MP_GEN_XS_16_64_256(func)                        \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_8_16_64_256(func)                      \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_4_8_16_64_256(func)                    \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)  \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)  \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16) \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(func)            \
  func(2,   JLN_MP_XS_2,   JLN_MP_RXS_2,   JLN_MP_REPEAT_2)   \
  func(4,   JLN_MP_XS_4,   JLN_MP_RXS_4,   JLN_MP_REPEAT_4)   \
  func(8,   JLN_MP_XS_8,   JLN_MP_RXS_8,   JLN_MP_REPEAT_8)   \
  func(16,  JLN_MP_XS_16,  JLN_MP_RXS_16,  JLN_MP_REPEAT_16)  \
  func(32,  JLN_MP_XS_32,  JLN_MP_RXS_32,  JLN_MP_REPEAT_32)  \
  func(64,  JLN_MP_XS_64,  JLN_MP_RXS_64,  JLN_MP_REPEAT_64)  \
  func(128, JLN_MP_XS_128, JLN_MP_RXS_128, JLN_MP_REPEAT_128) \
  func(256, JLN_MP_XS_256, JLN_MP_RXS_256, JLN_MP_REPEAT_256)

#define JLN_MP_GEN_XS_0_TO_8(func)                    \
  func(0, JLN_MP_XS_0, JLN_MP_RXS_0, JLN_MP_REPEAT_0) \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_1_TO_8(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_2_TO_8(func)                    \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3) \
  func(4, JLN_MP_XS_4, JLN_MP_RXS_4, JLN_MP_REPEAT_4) \
  func(5, JLN_MP_XS_5, JLN_MP_RXS_5, JLN_MP_REPEAT_5) \
  func(6, JLN_MP_XS_6, JLN_MP_RXS_6, JLN_MP_REPEAT_6) \
  func(7, JLN_MP_XS_7, JLN_MP_RXS_7, JLN_MP_REPEAT_7)

#define JLN_MP_GEN_XS_0_TO_4(func)                    \
  func(0, JLN_MP_XS_0, JLN_MP_RXS_0, JLN_MP_REPEAT_0) \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)

#define JLN_MP_GEN_XS_1_TO_4(func)                    \
  func(1, JLN_MP_XS_1, JLN_MP_RXS_1, JLN_MP_REPEAT_1) \
  func(2, JLN_MP_XS_2, JLN_MP_RXS_2, JLN_MP_REPEAT_2) \
  func(3, JLN_MP_XS_3, JLN_MP_RXS_3, JLN_MP_REPEAT_3)


#define JLN_MP_REPEAT_0(x, between)
#define JLN_MP_REPEAT_1(x, B) x
#define JLN_MP_REPEAT_2(x, B) x B x
#define JLN_MP_REPEAT_3(x, B) x B x B x
#define JLN_MP_REPEAT_4(x, B) x B x B x B x
#define JLN_MP_REPEAT_5(x, B) x B x B x B x B x
#define JLN_MP_REPEAT_6(x, B) x B x B x B x B x B x
#define JLN_MP_REPEAT_7(x, B) x B x B x B x B x B x B x
#define JLN_MP_REPEAT_8(x, B) x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_16(x, B) \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_32(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_64(x, B)                                    \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_128(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_256(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_512(x, B)                                   \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x

#define JLN_MP_REPEAT_1024(x, B)                                  \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B \
  x B x B x B x B x B x B x B x B x B x B x B x B x B x B x B x


#define JLN_MP_XS_0(before, after, between)

#define JLN_MP_XS_1(before, after, between) \
  before _1 after

#define JLN_MP_XS_2(before, after, between) \
  before _1 after between before _2 after

#define JLN_MP_XS_3(before, after, between) \
  before _1 after between before _2 after between before _3 after

#define JLN_MP_XS_4(before, after, between) \
  before _1 after between before _2 after between before _3 after between before _4 after

#define JLN_MP_XS_5(before, after, between)                                                       \
  before _1 after between before _2 after between before _3 after between before _4 after between \
  before _5 after

#define JLN_MP_XS_6(before, after, between)                                                       \
  before _1 after between before _2 after between before _3 after between before _4 after between \
  before _5 after between before _6 after

#define JLN_MP_XS_7(before, after, between)                                                       \
  before _1 after between before _2 after between before _3 after between before _4 after between \
  before _5 after between before _6 after between before _7 after

#define JLN_MP_XS_8(before, after, between)                                                       \
  before _1 after between before _2 after between before _3 after between before _4 after between \
  before _5 after between before _6 after between before _7 after between before _8 after

#define JLN_MP_XS_16(before, after, between)                                                        \
  before _1 after between before _2 after between before _3 after between before _4 after between   \
  before _5 after between before _6 after between before _7 after between before _8 after between   \
  before _9 after between before _10 after between before _11 after between before _12 after between \
  before _13 after between before _14 after between before _15 after between before _16 after

#define JLN_MP_XS_32(before, after, between)                                                          \
  before _1 after between before _2 after between before _3 after between before _4 after between     \
  before _5 after between before _6 after between before _7 after between before _8 after between     \
  before _9 after between before _10 after between before _11 after between before _12 after between  \
  before _13 after between before _14 after between before _15 after between before _16 after between \
  before _17 after between before _18 after between before _19 after between before _20 after between \
  before _21 after between before _22 after between before _23 after between before _24 after between \
  before _25 after between before _26 after between before _27 after between before _28 after between \
  before _29 after between before _30 after between before _31 after between before _32 after

#define JLN_MP_XS_64(before, after, between)                                                          \
  before _1 after between before _2 after between before _3 after between before _4 after between     \
  before _5 after between before _6 after between before _7 after between before _8 after between     \
  before _9 after between before _10 after between before _11 after between before _12 after between   \
  before _13 after between before _14 after between before _15 after between before _16 after between \
  before _17 after between before _18 after between before _19 after between before _20 after between \
  before _21 after between before _22 after between before _23 after between before _24 after between \
  before _25 after between before _26 after between before _27 after between before _28 after between \
  before _29 after between before _30 after between before _31 after between before _32 after between \
  before _33 after between before _34 after between before _35 after between before _36 after between \
  before _37 after between before _38 after between before _39 after between before _40 after between \
  before _41 after between before _42 after between before _43 after between before _44 after between \
  before _45 after between before _46 after between before _47 after between before _48 after between \
  before _49 after between before _50 after between before _51 after between before _52 after between \
  before _53 after between before _54 after between before _55 after between before _56 after between \
  before _57 after between before _58 after between before _59 after between before _60 after between \
  before _61 after between before _62 after between before _63 after between before _64 after

#define JLN_MP_XS_128(before, after, between)                                                             \
  before _1 after between before _2 after between before _3 after between before _4 after between         \
  before _5 after between before _6 after between before _7 after between before _8 after between         \
  before _9 after between before _10 after between before _11 after between before _12 after between      \
  before _13 after between before _14 after between before _15 after between before _16 after between     \
  before _17 after between before _18 after between before _19 after between before _20 after between     \
  before _21 after between before _22 after between before _23 after between before _24 after between     \
  before _25 after between before _26 after between before _27 after between before _28 after between     \
  before _29 after between before _30 after between before _31 after between before _32 after between     \
  before _33 after between before _34 after between before _35 after between before _36 after between     \
  before _37 after between before _38 after between before _39 after between before _40 after between     \
  before _41 after between before _42 after between before _43 after between before _44 after between     \
  before _45 after between before _46 after between before _47 after between before _48 after between     \
  before _49 after between before _50 after between before _51 after between before _52 after between     \
  before _53 after between before _54 after between before _55 after between before _56 after between     \
  before _57 after between before _58 after between before _59 after between before _60 after between     \
  before _61 after between before _62 after between before _63 after between before _64 after between     \
  before _65 after between before _66 after between before _67 after between before _68 after between     \
  before _69 after between before _70 after between before _71 after between before _72 after between     \
  before _73 after between before _74 after between before _75 after between before _76 after between     \
  before _77 after between before _78 after between before _79 after between before _80 after between     \
  before _81 after between before _82 after between before _83 after between before _84 after between     \
  before _85 after between before _86 after between before _87 after between before _88 after between     \
  before _89 after between before _90 after between before _91 after between before _92 after between     \
  before _93 after between before _94 after between before _95 after between before _96 after between     \
  before _97 after between before _98 after between before _99 after between before _100 after between    \
  before _101 after between before _102 after between before _103 after between before _104 after between \
  before _105 after between before _106 after between before _107 after between before _108 after between \
  before _109 after between before _110 after between before _111 after between before _112 after between \
  before _113 after between before _114 after between before _115 after between before _116 after between \
  before _117 after between before _118 after between before _119 after between before _120 after between \
  before _121 after between before _122 after between before _123 after between before _124 after between \
  before _125 after between before _126 after between before _127 after between before _128 after

#define JLN_MP_XS_256(before, after, between)                                                             \
  before _1 after between before _2 after between before _3 after between before _4 after between         \
  before _5 after between before _6 after between before _7 after between before _8 after between         \
  before _9 after between before _10 after between before _11 after between before _12 after between       \
  before _13 after between before _14 after between before _15 after between before _16 after between     \
  before _17 after between before _18 after between before _19 after between before _20 after between     \
  before _21 after between before _22 after between before _23 after between before _24 after between     \
  before _25 after between before _26 after between before _27 after between before _28 after between     \
  before _29 after between before _30 after between before _31 after between before _32 after between     \
  before _33 after between before _34 after between before _35 after between before _36 after between     \
  before _37 after between before _38 after between before _39 after between before _40 after between     \
  before _41 after between before _42 after between before _43 after between before _44 after between     \
  before _45 after between before _46 after between before _47 after between before _48 after between     \
  before _49 after between before _50 after between before _51 after between before _52 after between     \
  before _53 after between before _54 after between before _55 after between before _56 after between     \
  before _57 after between before _58 after between before _59 after between before _60 after between     \
  before _61 after between before _62 after between before _63 after between before _64 after between     \
  before _65 after between before _66 after between before _67 after between before _68 after between     \
  before _69 after between before _70 after between before _71 after between before _72 after between     \
  before _73 after between before _74 after between before _75 after between before _76 after between     \
  before _77 after between before _78 after between before _79 after between before _80 after between     \
  before _81 after between before _82 after between before _83 after between before _84 after between     \
  before _85 after between before _86 after between before _87 after between before _88 after between     \
  before _89 after between before _90 after between before _91 after between before _92 after between     \
  before _93 after between before _94 after between before _95 after between before _96 after between     \
  before _97 after between before _98 after between before _99 after between before _100 after between     \
  before _101 after between before _102 after between before _103 after between before _104 after between \
  before _105 after between before _106 after between before _107 after between before _108 after between \
  before _109 after between before _110 after between before _111 after between before _112 after between \
  before _113 after between before _114 after between before _115 after between before _116 after between \
  before _117 after between before _118 after between before _119 after between before _120 after between \
  before _121 after between before _122 after between before _123 after between before _124 after between \
  before _125 after between before _126 after between before _127 after between before _128 after between \
  before _129 after between before _130 after between before _131 after between before _132 after between \
  before _133 after between before _134 after between before _135 after between before _136 after between \
  before _137 after between before _138 after between before _139 after between before _140 after between \
  before _141 after between before _142 after between before _143 after between before _144 after between \
  before _145 after between before _146 after between before _147 after between before _148 after between \
  before _149 after between before _150 after between before _151 after between before _152 after between \
  before _153 after between before _154 after between before _155 after between before _156 after between \
  before _157 after between before _158 after between before _159 after between before _160 after between \
  before _161 after between before _162 after between before _163 after between before _164 after between \
  before _165 after between before _166 after between before _167 after between before _168 after between \
  before _169 after between before _170 after between before _171 after between before _172 after between \
  before _173 after between before _174 after between before _175 after between before _176 after between \
  before _177 after between before _178 after between before _179 after between before _180 after between \
  before _181 after between before _182 after between before _183 after between before _184 after between \
  before _185 after between before _186 after between before _187 after between before _188 after between \
  before _189 after between before _190 after between before _191 after between before _192 after between \
  before _193 after between before _194 after between before _195 after between before _196 after between \
  before _197 after between before _198 after between before _199 after between before _200 after between \
  before _201 after between before _202 after between before _203 after between before _204 after between \
  before _205 after between before _206 after between before _207 after between before _208 after between \
  before _209 after between before _210 after between before _211 after between before _212 after between \
  before _213 after between before _214 after between before _215 after between before _216 after between \
  before _217 after between before _218 after between before _219 after between before _220 after between \
  before _221 after between before _222 after between before _223 after between before _224 after between \
  before _225 after between before _226 after between before _227 after between before _228 after between \
  before _229 after between before _230 after between before _231 after between before _232 after between \
  before _233 after between before _234 after between before _235 after between before _236 after between \
  before _237 after between before _238 after between before _239 after between before _240 after between \
  before _241 after between before _242 after between before _243 after between before _244 after between \
  before _245 after between before _246 after between before _247 after between before _248 after between \
  before _249 after between before _250 after between before _251 after between before _252 after between \
  before _253 after between before _254 after between before _255 after between before _256 after

#define JLN_MP_XS_512(before, after, between)                                                             \
  before _1 after between before _2 after between before _3 after between before _4 after between         \
  before _5 after between before _6 after between before _7 after between before _8 after between         \
  before _9 after between before _10 after between before _11 after between before _12 after between      \
  before _13 after between before _14 after between before _15 after between before _16 after between     \
  before _17 after between before _18 after between before _19 after between before _20 after between     \
  before _21 after between before _22 after between before _23 after between before _24 after between     \
  before _25 after between before _26 after between before _27 after between before _28 after between     \
  before _29 after between before _30 after between before _31 after between before _32 after between     \
  before _33 after between before _34 after between before _35 after between before _36 after between     \
  before _37 after between before _38 after between before _39 after between before _40 after between     \
  before _41 after between before _42 after between before _43 after between before _44 after between     \
  before _45 after between before _46 after between before _47 after between before _48 after between     \
  before _49 after between before _50 after between before _51 after between before _52 after between     \
  before _53 after between before _54 after between before _55 after between before _56 after between     \
  before _57 after between before _58 after between before _59 after between before _60 after between     \
  before _61 after between before _62 after between before _63 after between before _64 after between     \
  before _65 after between before _66 after between before _67 after between before _68 after between     \
  before _69 after between before _70 after between before _71 after between before _72 after between     \
  before _73 after between before _74 after between before _75 after between before _76 after between     \
  before _77 after between before _78 after between before _79 after between before _80 after between     \
  before _81 after between before _82 after between before _83 after between before _84 after between     \
  before _85 after between before _86 after between before _87 after between before _88 after between     \
  before _89 after between before _90 after between before _91 after between before _92 after between     \
  before _93 after between before _94 after between before _95 after between before _96 after between     \
  before _97 after between before _98 after between before _99 after between before _100 after between    \
  before _101 after between before _102 after between before _103 after between before _104 after between \
  before _105 after between before _106 after between before _107 after between before _108 after between \
  before _109 after between before _110 after between before _111 after between before _112 after between \
  before _113 after between before _114 after between before _115 after between before _116 after between \
  before _117 after between before _118 after between before _119 after between before _120 after between \
  before _121 after between before _122 after between before _123 after between before _124 after between \
  before _125 after between before _126 after between before _127 after between before _128 after between \
  before _129 after between before _130 after between before _131 after between before _132 after between \
  before _133 after between before _134 after between before _135 after between before _136 after between \
  before _137 after between before _138 after between before _139 after between before _140 after between \
  before _141 after between before _142 after between before _143 after between before _144 after between \
  before _145 after between before _146 after between before _147 after between before _148 after between \
  before _149 after between before _150 after between before _151 after between before _152 after between \
  before _153 after between before _154 after between before _155 after between before _156 after between \
  before _157 after between before _158 after between before _159 after between before _160 after between \
  before _161 after between before _162 after between before _163 after between before _164 after between \
  before _165 after between before _166 after between before _167 after between before _168 after between \
  before _169 after between before _170 after between before _171 after between before _172 after between \
  before _173 after between before _174 after between before _175 after between before _176 after between \
  before _177 after between before _178 after between before _179 after between before _180 after between \
  before _181 after between before _182 after between before _183 after between before _184 after between \
  before _185 after between before _186 after between before _187 after between before _188 after between \
  before _189 after between before _190 after between before _191 after between before _192 after between \
  before _193 after between before _194 after between before _195 after between before _196 after between \
  before _197 after between before _198 after between before _199 after between before _200 after between \
  before _201 after between before _202 after between before _203 after between before _204 after between \
  before _205 after between before _206 after between before _207 after between before _208 after between \
  before _209 after between before _210 after between before _211 after between before _212 after between \
  before _213 after between before _214 after between before _215 after between before _216 after between \
  before _217 after between before _218 after between before _219 after between before _220 after between \
  before _221 after between before _222 after between before _223 after between before _224 after between \
  before _225 after between before _226 after between before _227 after between before _228 after between \
  before _229 after between before _230 after between before _231 after between before _232 after between \
  before _233 after between before _234 after between before _235 after between before _236 after between \
  before _237 after between before _238 after between before _239 after between before _240 after between \
  before _241 after between before _242 after between before _243 after between before _244 after between \
  before _245 after between before _246 after between before _247 after between before _248 after between \
  before _249 after between before _250 after between before _251 after between before _252 after between \
  before _253 after between before _254 after between before _255 after between before _256 after between \
  before _257 after between before _258 after between before _259 after between before _260 after between \
  before _261 after between before _262 after between before _263 after between before _264 after between \
  before _265 after between before _266 after between before _267 after between before _268 after between \
  before _269 after between before _270 after between before _271 after between before _272 after between \
  before _273 after between before _274 after between before _275 after between before _276 after between \
  before _277 after between before _278 after between before _279 after between before _280 after between \
  before _281 after between before _282 after between before _283 after between before _284 after between \
  before _285 after between before _286 after between before _287 after between before _288 after between \
  before _289 after between before _290 after between before _291 after between before _292 after between \
  before _293 after between before _294 after between before _295 after between before _296 after between \
  before _297 after between before _298 after between before _299 after between before _300 after between \
  before _301 after between before _302 after between before _303 after between before _304 after between \
  before _305 after between before _306 after between before _307 after between before _308 after between \
  before _309 after between before _310 after between before _311 after between before _312 after between \
  before _313 after between before _314 after between before _315 after between before _316 after between \
  before _317 after between before _318 after between before _319 after between before _320 after between \
  before _321 after between before _322 after between before _323 after between before _324 after between \
  before _325 after between before _326 after between before _327 after between before _328 after between \
  before _329 after between before _330 after between before _331 after between before _332 after between \
  before _333 after between before _334 after between before _335 after between before _336 after between \
  before _337 after between before _338 after between before _339 after between before _340 after between \
  before _341 after between before _342 after between before _343 after between before _344 after between \
  before _345 after between before _346 after between before _347 after between before _348 after between \
  before _349 after between before _350 after between before _351 after between before _352 after between \
  before _353 after between before _354 after between before _355 after between before _356 after between \
  before _357 after between before _358 after between before _359 after between before _360 after between \
  before _361 after between before _362 after between before _363 after between before _364 after between \
  before _365 after between before _366 after between before _367 after between before _368 after between \
  before _369 after between before _370 after between before _371 after between before _372 after between \
  before _373 after between before _374 after between before _375 after between before _376 after between \
  before _377 after between before _378 after between before _379 after between before _380 after between \
  before _381 after between before _382 after between before _383 after between before _384 after between \
  before _385 after between before _386 after between before _387 after between before _388 after between \
  before _389 after between before _390 after between before _391 after between before _392 after between \
  before _393 after between before _394 after between before _395 after between before _396 after between \
  before _397 after between before _398 after between before _399 after between before _400 after between \
  before _401 after between before _402 after between before _403 after between before _404 after between \
  before _405 after between before _406 after between before _407 after between before _408 after between \
  before _409 after between before _410 after between before _411 after between before _412 after between \
  before _413 after between before _414 after between before _415 after between before _416 after between \
  before _417 after between before _418 after between before _419 after between before _420 after between \
  before _421 after between before _422 after between before _423 after between before _424 after between \
  before _425 after between before _426 after between before _427 after between before _428 after between \
  before _429 after between before _430 after between before _431 after between before _432 after between \
  before _433 after between before _434 after between before _435 after between before _436 after between \
  before _437 after between before _438 after between before _439 after between before _440 after between \
  before _441 after between before _442 after between before _443 after between before _444 after between \
  before _445 after between before _446 after between before _447 after between before _448 after between \
  before _449 after between before _450 after between before _451 after between before _452 after between \
  before _453 after between before _454 after between before _455 after between before _456 after between \
  before _457 after between before _458 after between before _459 after between before _460 after between \
  before _461 after between before _462 after between before _463 after between before _464 after between \
  before _465 after between before _466 after between before _467 after between before _468 after between \
  before _469 after between before _470 after between before _471 after between before _472 after between \
  before _473 after between before _474 after between before _475 after between before _476 after between \
  before _477 after between before _478 after between before _479 after between before _480 after between \
  before _481 after between before _482 after between before _483 after between before _484 after between \
  before _485 after between before _486 after between before _487 after between before _488 after between \
  before _489 after between before _490 after between before _491 after between before _492 after between \
  before _493 after between before _494 after between before _495 after between before _496 after between \
  before _497 after between before _498 after between before _499 after between before _500 after between \
  before _501 after between before _502 after between before _503 after between before _504 after between \
  before _505 after between before _506 after between before _507 after between before _508 after between \
  before _509 after between before _510 after between before _511 after between before _512 after

#define JLN_MP_XS_1024(before, after, between)                                                                \
  before _1 after between before _2 after between before _3 after between before _4 after between             \
  before _5 after between before _6 after between before _7 after between before _8 after between             \
  before _9 after between before _10 after between before _11 after between before _12 after between           \
  before _13 after between before _14 after between before _15 after between before _16 after between         \
  before _17 after between before _18 after between before _19 after between before _20 after between         \
  before _21 after between before _22 after between before _23 after between before _24 after between         \
  before _25 after between before _26 after between before _27 after between before _28 after between         \
  before _29 after between before _30 after between before _31 after between before _32 after between         \
  before _33 after between before _34 after between before _35 after between before _36 after between         \
  before _37 after between before _38 after between before _39 after between before _40 after between         \
  before _41 after between before _42 after between before _43 after between before _44 after between         \
  before _45 after between before _46 after between before _47 after between before _48 after between         \
  before _49 after between before _50 after between before _51 after between before _52 after between         \
  before _53 after between before _54 after between before _55 after between before _56 after between         \
  before _57 after between before _58 after between before _59 after between before _60 after between         \
  before _61 after between before _62 after between before _63 after between before _64 after between         \
  before _65 after between before _66 after between before _67 after between before _68 after between         \
  before _69 after between before _70 after between before _71 after between before _72 after between         \
  before _73 after between before _74 after between before _75 after between before _76 after between         \
  before _77 after between before _78 after between before _79 after between before _80 after between         \
  before _81 after between before _82 after between before _83 after between before _84 after between         \
  before _85 after between before _86 after between before _87 after between before _88 after between         \
  before _89 after between before _90 after between before _91 after between before _92 after between         \
  before _93 after between before _94 after between before _95 after between before _96 after between         \
  before _97 after between before _98 after between before _99 after between before _100 after between         \
  before _101 after between before _102 after between before _103 after between before _104 after between     \
  before _105 after between before _106 after between before _107 after between before _108 after between     \
  before _109 after between before _110 after between before _111 after between before _112 after between     \
  before _113 after between before _114 after between before _115 after between before _116 after between     \
  before _117 after between before _118 after between before _119 after between before _120 after between     \
  before _121 after between before _122 after between before _123 after between before _124 after between     \
  before _125 after between before _126 after between before _127 after between before _128 after between     \
  before _129 after between before _130 after between before _131 after between before _132 after between     \
  before _133 after between before _134 after between before _135 after between before _136 after between     \
  before _137 after between before _138 after between before _139 after between before _140 after between     \
  before _141 after between before _142 after between before _143 after between before _144 after between     \
  before _145 after between before _146 after between before _147 after between before _148 after between     \
  before _149 after between before _150 after between before _151 after between before _152 after between     \
  before _153 after between before _154 after between before _155 after between before _156 after between     \
  before _157 after between before _158 after between before _159 after between before _160 after between     \
  before _161 after between before _162 after between before _163 after between before _164 after between     \
  before _165 after between before _166 after between before _167 after between before _168 after between     \
  before _169 after between before _170 after between before _171 after between before _172 after between     \
  before _173 after between before _174 after between before _175 after between before _176 after between     \
  before _177 after between before _178 after between before _179 after between before _180 after between     \
  before _181 after between before _182 after between before _183 after between before _184 after between     \
  before _185 after between before _186 after between before _187 after between before _188 after between     \
  before _189 after between before _190 after between before _191 after between before _192 after between     \
  before _193 after between before _194 after between before _195 after between before _196 after between     \
  before _197 after between before _198 after between before _199 after between before _200 after between     \
  before _201 after between before _202 after between before _203 after between before _204 after between     \
  before _205 after between before _206 after between before _207 after between before _208 after between     \
  before _209 after between before _210 after between before _211 after between before _212 after between     \
  before _213 after between before _214 after between before _215 after between before _216 after between     \
  before _217 after between before _218 after between before _219 after between before _220 after between     \
  before _221 after between before _222 after between before _223 after between before _224 after between     \
  before _225 after between before _226 after between before _227 after between before _228 after between     \
  before _229 after between before _230 after between before _231 after between before _232 after between     \
  before _233 after between before _234 after between before _235 after between before _236 after between     \
  before _237 after between before _238 after between before _239 after between before _240 after between     \
  before _241 after between before _242 after between before _243 after between before _244 after between     \
  before _245 after between before _246 after between before _247 after between before _248 after between     \
  before _249 after between before _250 after between before _251 after between before _252 after between     \
  before _253 after between before _254 after between before _255 after between before _256 after between     \
  before _257 after between before _258 after between before _259 after between before _260 after between     \
  before _261 after between before _262 after between before _263 after between before _264 after between     \
  before _265 after between before _266 after between before _267 after between before _268 after between     \
  before _269 after between before _270 after between before _271 after between before _272 after between     \
  before _273 after between before _274 after between before _275 after between before _276 after between     \
  before _277 after between before _278 after between before _279 after between before _280 after between     \
  before _281 after between before _282 after between before _283 after between before _284 after between     \
  before _285 after between before _286 after between before _287 after between before _288 after between     \
  before _289 after between before _290 after between before _291 after between before _292 after between     \
  before _293 after between before _294 after between before _295 after between before _296 after between     \
  before _297 after between before _298 after between before _299 after between before _300 after between     \
  before _301 after between before _302 after between before _303 after between before _304 after between     \
  before _305 after between before _306 after between before _307 after between before _308 after between     \
  before _309 after between before _310 after between before _311 after between before _312 after between     \
  before _313 after between before _314 after between before _315 after between before _316 after between     \
  before _317 after between before _318 after between before _319 after between before _320 after between     \
  before _321 after between before _322 after between before _323 after between before _324 after between     \
  before _325 after between before _326 after between before _327 after between before _328 after between     \
  before _329 after between before _330 after between before _331 after between before _332 after between     \
  before _333 after between before _334 after between before _335 after between before _336 after between     \
  before _337 after between before _338 after between before _339 after between before _340 after between     \
  before _341 after between before _342 after between before _343 after between before _344 after between     \
  before _345 after between before _346 after between before _347 after between before _348 after between     \
  before _349 after between before _350 after between before _351 after between before _352 after between     \
  before _353 after between before _354 after between before _355 after between before _356 after between     \
  before _357 after between before _358 after between before _359 after between before _360 after between     \
  before _361 after between before _362 after between before _363 after between before _364 after between     \
  before _365 after between before _366 after between before _367 after between before _368 after between     \
  before _369 after between before _370 after between before _371 after between before _372 after between     \
  before _373 after between before _374 after between before _375 after between before _376 after between     \
  before _377 after between before _378 after between before _379 after between before _380 after between     \
  before _381 after between before _382 after between before _383 after between before _384 after between     \
  before _385 after between before _386 after between before _387 after between before _388 after between     \
  before _389 after between before _390 after between before _391 after between before _392 after between     \
  before _393 after between before _394 after between before _395 after between before _396 after between     \
  before _397 after between before _398 after between before _399 after between before _400 after between     \
  before _401 after between before _402 after between before _403 after between before _404 after between     \
  before _405 after between before _406 after between before _407 after between before _408 after between     \
  before _409 after between before _410 after between before _411 after between before _412 after between     \
  before _413 after between before _414 after between before _415 after between before _416 after between     \
  before _417 after between before _418 after between before _419 after between before _420 after between     \
  before _421 after between before _422 after between before _423 after between before _424 after between     \
  before _425 after between before _426 after between before _427 after between before _428 after between     \
  before _429 after between before _430 after between before _431 after between before _432 after between     \
  before _433 after between before _434 after between before _435 after between before _436 after between     \
  before _437 after between before _438 after between before _439 after between before _440 after between     \
  before _441 after between before _442 after between before _443 after between before _444 after between     \
  before _445 after between before _446 after between before _447 after between before _448 after between     \
  before _449 after between before _450 after between before _451 after between before _452 after between     \
  before _453 after between before _454 after between before _455 after between before _456 after between     \
  before _457 after between before _458 after between before _459 after between before _460 after between     \
  before _461 after between before _462 after between before _463 after between before _464 after between     \
  before _465 after between before _466 after between before _467 after between before _468 after between     \
  before _469 after between before _470 after between before _471 after between before _472 after between     \
  before _473 after between before _474 after between before _475 after between before _476 after between     \
  before _477 after between before _478 after between before _479 after between before _480 after between     \
  before _481 after between before _482 after between before _483 after between before _484 after between     \
  before _485 after between before _486 after between before _487 after between before _488 after between     \
  before _489 after between before _490 after between before _491 after between before _492 after between     \
  before _493 after between before _494 after between before _495 after between before _496 after between     \
  before _497 after between before _498 after between before _499 after between before _500 after between     \
  before _501 after between before _502 after between before _503 after between before _504 after between     \
  before _505 after between before _506 after between before _507 after between before _508 after between     \
  before _509 after between before _510 after between before _511 after between before _512 after between     \
  before _513 after between before _514 after between before _515 after between before _516 after between     \
  before _517 after between before _518 after between before _519 after between before _520 after between     \
  before _521 after between before _522 after between before _523 after between before _524 after between     \
  before _525 after between before _526 after between before _527 after between before _528 after between     \
  before _529 after between before _530 after between before _531 after between before _532 after between     \
  before _533 after between before _534 after between before _535 after between before _536 after between     \
  before _537 after between before _538 after between before _539 after between before _540 after between     \
  before _541 after between before _542 after between before _543 after between before _544 after between     \
  before _545 after between before _546 after between before _547 after between before _548 after between     \
  before _549 after between before _550 after between before _551 after between before _552 after between     \
  before _553 after between before _554 after between before _555 after between before _556 after between     \
  before _557 after between before _558 after between before _559 after between before _560 after between     \
  before _561 after between before _562 after between before _563 after between before _564 after between     \
  before _565 after between before _566 after between before _567 after between before _568 after between     \
  before _569 after between before _570 after between before _571 after between before _572 after between     \
  before _573 after between before _574 after between before _575 after between before _576 after between     \
  before _577 after between before _578 after between before _579 after between before _580 after between     \
  before _581 after between before _582 after between before _583 after between before _584 after between     \
  before _585 after between before _586 after between before _587 after between before _588 after between     \
  before _589 after between before _590 after between before _591 after between before _592 after between     \
  before _593 after between before _594 after between before _595 after between before _596 after between     \
  before _597 after between before _598 after between before _599 after between before _600 after between     \
  before _601 after between before _602 after between before _603 after between before _604 after between     \
  before _605 after between before _606 after between before _607 after between before _608 after between     \
  before _609 after between before _610 after between before _611 after between before _612 after between     \
  before _613 after between before _614 after between before _615 after between before _616 after between     \
  before _617 after between before _618 after between before _619 after between before _620 after between     \
  before _621 after between before _622 after between before _623 after between before _624 after between     \
  before _625 after between before _626 after between before _627 after between before _628 after between     \
  before _629 after between before _630 after between before _631 after between before _632 after between     \
  before _633 after between before _634 after between before _635 after between before _636 after between     \
  before _637 after between before _638 after between before _639 after between before _640 after between     \
  before _641 after between before _642 after between before _643 after between before _644 after between     \
  before _645 after between before _646 after between before _647 after between before _648 after between     \
  before _649 after between before _650 after between before _651 after between before _652 after between     \
  before _653 after between before _654 after between before _655 after between before _656 after between     \
  before _657 after between before _658 after between before _659 after between before _660 after between     \
  before _661 after between before _662 after between before _663 after between before _664 after between     \
  before _665 after between before _666 after between before _667 after between before _668 after between     \
  before _669 after between before _670 after between before _671 after between before _672 after between     \
  before _673 after between before _674 after between before _675 after between before _676 after between     \
  before _677 after between before _678 after between before _679 after between before _680 after between     \
  before _681 after between before _682 after between before _683 after between before _684 after between     \
  before _685 after between before _686 after between before _687 after between before _688 after between     \
  before _689 after between before _690 after between before _691 after between before _692 after between     \
  before _693 after between before _694 after between before _695 after between before _696 after between     \
  before _697 after between before _698 after between before _699 after between before _700 after between     \
  before _701 after between before _702 after between before _703 after between before _704 after between     \
  before _705 after between before _706 after between before _707 after between before _708 after between     \
  before _709 after between before _710 after between before _711 after between before _712 after between     \
  before _713 after between before _714 after between before _715 after between before _716 after between     \
  before _717 after between before _718 after between before _719 after between before _720 after between     \
  before _721 after between before _722 after between before _723 after between before _724 after between     \
  before _725 after between before _726 after between before _727 after between before _728 after between     \
  before _729 after between before _730 after between before _731 after between before _732 after between     \
  before _733 after between before _734 after between before _735 after between before _736 after between     \
  before _737 after between before _738 after between before _739 after between before _740 after between     \
  before _741 after between before _742 after between before _743 after between before _744 after between     \
  before _745 after between before _746 after between before _747 after between before _748 after between     \
  before _749 after between before _750 after between before _751 after between before _752 after between     \
  before _753 after between before _754 after between before _755 after between before _756 after between     \
  before _757 after between before _758 after between before _759 after between before _760 after between     \
  before _761 after between before _762 after between before _763 after between before _764 after between     \
  before _765 after between before _766 after between before _767 after between before _768 after between     \
  before _769 after between before _770 after between before _771 after between before _772 after between     \
  before _773 after between before _774 after between before _775 after between before _776 after between     \
  before _777 after between before _778 after between before _779 after between before _780 after between     \
  before _781 after between before _782 after between before _783 after between before _784 after between     \
  before _785 after between before _786 after between before _787 after between before _788 after between     \
  before _789 after between before _790 after between before _791 after between before _792 after between     \
  before _793 after between before _794 after between before _795 after between before _796 after between     \
  before _797 after between before _798 after between before _799 after between before _800 after between     \
  before _801 after between before _802 after between before _803 after between before _804 after between     \
  before _805 after between before _806 after between before _807 after between before _808 after between     \
  before _809 after between before _810 after between before _811 after between before _812 after between     \
  before _813 after between before _814 after between before _815 after between before _816 after between     \
  before _817 after between before _818 after between before _819 after between before _820 after between     \
  before _821 after between before _822 after between before _823 after between before _824 after between     \
  before _825 after between before _826 after between before _827 after between before _828 after between     \
  before _829 after between before _830 after between before _831 after between before _832 after between     \
  before _833 after between before _834 after between before _835 after between before _836 after between     \
  before _837 after between before _838 after between before _839 after between before _840 after between     \
  before _841 after between before _842 after between before _843 after between before _844 after between     \
  before _845 after between before _846 after between before _847 after between before _848 after between     \
  before _849 after between before _850 after between before _851 after between before _852 after between     \
  before _853 after between before _854 after between before _855 after between before _856 after between     \
  before _857 after between before _858 after between before _859 after between before _860 after between     \
  before _861 after between before _862 after between before _863 after between before _864 after between     \
  before _865 after between before _866 after between before _867 after between before _868 after between     \
  before _869 after between before _870 after between before _871 after between before _872 after between     \
  before _873 after between before _874 after between before _875 after between before _876 after between     \
  before _877 after between before _878 after between before _879 after between before _880 after between     \
  before _881 after between before _882 after between before _883 after between before _884 after between     \
  before _885 after between before _886 after between before _887 after between before _888 after between     \
  before _889 after between before _890 after between before _891 after between before _892 after between     \
  before _893 after between before _894 after between before _895 after between before _896 after between     \
  before _897 after between before _898 after between before _899 after between before _900 after between     \
  before _901 after between before _902 after between before _903 after between before _904 after between     \
  before _905 after between before _906 after between before _907 after between before _908 after between     \
  before _909 after between before _910 after between before _911 after between before _912 after between     \
  before _913 after between before _914 after between before _915 after between before _916 after between     \
  before _917 after between before _918 after between before _919 after between before _920 after between     \
  before _921 after between before _922 after between before _923 after between before _924 after between     \
  before _925 after between before _926 after between before _927 after between before _928 after between     \
  before _929 after between before _930 after between before _931 after between before _932 after between     \
  before _933 after between before _934 after between before _935 after between before _936 after between     \
  before _937 after between before _938 after between before _939 after between before _940 after between     \
  before _941 after between before _942 after between before _943 after between before _944 after between     \
  before _945 after between before _946 after between before _947 after between before _948 after between     \
  before _949 after between before _950 after between before _951 after between before _952 after between     \
  before _953 after between before _954 after between before _955 after between before _956 after between     \
  before _957 after between before _958 after between before _959 after between before _960 after between     \
  before _961 after between before _962 after between before _963 after between before _964 after between     \
  before _965 after between before _966 after between before _967 after between before _968 after between     \
  before _969 after between before _970 after between before _971 after between before _972 after between     \
  before _973 after between before _974 after between before _975 after between before _976 after between     \
  before _977 after between before _978 after between before _979 after between before _980 after between     \
  before _981 after between before _982 after between before _983 after between before _984 after between     \
  before _985 after between before _986 after between before _987 after between before _988 after between     \
  before _989 after between before _990 after between before _991 after between before _992 after between     \
  before _993 after between before _994 after between before _995 after between before _996 after between     \
  before _997 after between before _998 after between before _999 after between before _1000 after between     \
  before _1001 after between before _1002 after between before _1003 after between before _1004 after between \
  before _1005 after between before _1006 after between before _1007 after between before _1008 after between \
  before _1009 after between before _1010 after between before _1011 after between before _1012 after between \
  before _1013 after between before _1014 after between before _1015 after between before _1016 after between \
  before _1017 after between before _1018 after between before _1019 after between before _1020 after between \
  before _1021 after between before _1022 after between before _1023 after between before _1024 after

#define JLN_MP_RXS_0(before, after, between)

#define JLN_MP_RXS_1(before, after, between) \
  before _1 after

#define JLN_MP_RXS_2(before, after, between) \
  before _2 after between before _1 after

#define JLN_MP_RXS_3(before, after, between) \
  before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_4(before, after, between) \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_5(before, after, between) \
  before _5 after between before _4 after between before _3 after between before _2 after between \
  before _1 after

#define JLN_MP_RXS_6(before, after, between)                                                      \
  before _6 after between before _5 after between before _4 after between before _3 after between \
  before _2 after between before _1 after

#define JLN_MP_RXS_7(before, after, between)                                                      \
  before _7 after between before _6 after between before _5 after between before _4 after between \
  before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_8(before, after, between)                                                      \
  before _8 after between before _7 after between before _6 after between before _5 after between \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_16(before, after, between)                                                         \
  before _16 after between before _15 after between before _14 after between before _13 after between \
  before _12 after between before _11 after between before _10 after between before _9 after between   \
  before _8 after between before _7 after between before _6 after between before _5 after between     \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_32(before, after, between)                                                         \
  before _32 after between before _31 after between before _30 after between before _29 after between \
  before _28 after between before _27 after between before _26 after between before _25 after between \
  before _24 after between before _23 after between before _22 after between before _21 after between \
  before _20 after between before _19 after between before _18 after between before _17 after between \
  before _16 after between before _15 after between before _14 after between before _13 after between \
  before _12 after between before _11 after between before _10 after between before _9 after between  \
  before _8 after between before _7 after between before _6 after between before _5 after between     \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_64(before, after, between)                                                         \
  before _64 after between before _63 after between before _62 after between before _61 after between \
  before _60 after between before _59 after between before _58 after between before _57 after between \
  before _56 after between before _55 after between before _54 after between before _53 after between \
  before _52 after between before _51 after between before _50 after between before _49 after between \
  before _48 after between before _47 after between before _46 after between before _45 after between \
  before _44 after between before _43 after between before _42 after between before _41 after between \
  before _40 after between before _39 after between before _38 after between before _37 after between \
  before _36 after between before _35 after between before _34 after between before _33 after between \
  before _32 after between before _31 after between before _30 after between before _29 after between \
  before _28 after between before _27 after between before _26 after between before _25 after between \
  before _24 after between before _23 after between before _22 after between before _21 after between \
  before _20 after between before _19 after between before _18 after between before _17 after between \
  before _16 after between before _15 after between before _14 after between before _13 after between \
  before _12 after between before _11 after between before _10 after between before _9 after between   \
  before _8 after between before _7 after between before _6 after between before _5 after between     \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_128(before, after, between)                                                            \
  before _128 after between before _127 after between before _126 after between before _125 after between \
  before _124 after between before _123 after between before _122 after between before _121 after between \
  before _120 after between before _119 after between before _118 after between before _117 after between \
  before _116 after between before _115 after between before _114 after between before _113 after between \
  before _112 after between before _111 after between before _110 after between before _109 after between \
  before _108 after between before _107 after between before _106 after between before _105 after between \
  before _104 after between before _103 after between before _102 after between before _101 after between \
  before _100 after between before _99 after between before _98 after between before _97 after between     \
  before _96 after between before _95 after between before _94 after between before _93 after between     \
  before _92 after between before _91 after between before _90 after between before _89 after between     \
  before _88 after between before _87 after between before _86 after between before _85 after between     \
  before _84 after between before _83 after between before _82 after between before _81 after between     \
  before _80 after between before _79 after between before _78 after between before _77 after between     \
  before _76 after between before _75 after between before _74 after between before _73 after between     \
  before _72 after between before _71 after between before _70 after between before _69 after between     \
  before _68 after between before _67 after between before _66 after between before _65 after between     \
  before _64 after between before _63 after between before _62 after between before _61 after between     \
  before _60 after between before _59 after between before _58 after between before _57 after between     \
  before _56 after between before _55 after between before _54 after between before _53 after between     \
  before _52 after between before _51 after between before _50 after between before _49 after between     \
  before _48 after between before _47 after between before _46 after between before _45 after between     \
  before _44 after between before _43 after between before _42 after between before _41 after between     \
  before _40 after between before _39 after between before _38 after between before _37 after between     \
  before _36 after between before _35 after between before _34 after between before _33 after between     \
  before _32 after between before _31 after between before _30 after between before _29 after between     \
  before _28 after between before _27 after between before _26 after between before _25 after between     \
  before _24 after between before _23 after between before _22 after between before _21 after between     \
  before _20 after between before _19 after between before _18 after between before _17 after between     \
  before _16 after between before _15 after between before _14 after between before _13 after between     \
  before _12 after between before _11 after between before _10 after between before _9 after between       \
  before _8 after between before _7 after between before _6 after between before _5 after between         \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_256(before, after, between)                                                            \
  before _256 after between before _255 after between before _254 after between before _253 after between \
  before _252 after between before _251 after between before _250 after between before _249 after between \
  before _248 after between before _247 after between before _246 after between before _245 after between \
  before _244 after between before _243 after between before _242 after between before _241 after between \
  before _240 after between before _239 after between before _238 after between before _237 after between \
  before _236 after between before _235 after between before _234 after between before _233 after between \
  before _232 after between before _231 after between before _230 after between before _229 after between \
  before _228 after between before _227 after between before _226 after between before _225 after between \
  before _224 after between before _223 after between before _222 after between before _221 after between \
  before _220 after between before _219 after between before _218 after between before _217 after between \
  before _216 after between before _215 after between before _214 after between before _213 after between \
  before _212 after between before _211 after between before _210 after between before _209 after between \
  before _208 after between before _207 after between before _206 after between before _205 after between \
  before _204 after between before _203 after between before _202 after between before _201 after between \
  before _200 after between before _199 after between before _198 after between before _197 after between \
  before _196 after between before _195 after between before _194 after between before _193 after between \
  before _192 after between before _191 after between before _190 after between before _189 after between \
  before _188 after between before _187 after between before _186 after between before _185 after between \
  before _184 after between before _183 after between before _182 after between before _181 after between \
  before _180 after between before _179 after between before _178 after between before _177 after between \
  before _176 after between before _175 after between before _174 after between before _173 after between \
  before _172 after between before _171 after between before _170 after between before _169 after between \
  before _168 after between before _167 after between before _166 after between before _165 after between \
  before _164 after between before _163 after between before _162 after between before _161 after between \
  before _160 after between before _159 after between before _158 after between before _157 after between \
  before _156 after between before _155 after between before _154 after between before _153 after between \
  before _152 after between before _151 after between before _150 after between before _149 after between \
  before _148 after between before _147 after between before _146 after between before _145 after between \
  before _144 after between before _143 after between before _142 after between before _141 after between \
  before _140 after between before _139 after between before _138 after between before _137 after between \
  before _136 after between before _135 after between before _134 after between before _133 after between \
  before _132 after between before _131 after between before _130 after between before _129 after between \
  before _128 after between before _127 after between before _126 after between before _125 after between \
  before _124 after between before _123 after between before _122 after between before _121 after between \
  before _120 after between before _119 after between before _118 after between before _117 after between \
  before _116 after between before _115 after between before _114 after between before _113 after between \
  before _112 after between before _111 after between before _110 after between before _109 after between \
  before _108 after between before _107 after between before _106 after between before _105 after between \
  before _104 after between before _103 after between before _102 after between before _101 after between \
  before _100 after between before _99 after between before _98 after between before _97 after between     \
  before _96 after between before _95 after between before _94 after between before _93 after between     \
  before _92 after between before _91 after between before _90 after between before _89 after between     \
  before _88 after between before _87 after between before _86 after between before _85 after between     \
  before _84 after between before _83 after between before _82 after between before _81 after between     \
  before _80 after between before _79 after between before _78 after between before _77 after between     \
  before _76 after between before _75 after between before _74 after between before _73 after between     \
  before _72 after between before _71 after between before _70 after between before _69 after between     \
  before _68 after between before _67 after between before _66 after between before _65 after between     \
  before _64 after between before _63 after between before _62 after between before _61 after between     \
  before _60 after between before _59 after between before _58 after between before _57 after between     \
  before _56 after between before _55 after between before _54 after between before _53 after between     \
  before _52 after between before _51 after between before _50 after between before _49 after between     \
  before _48 after between before _47 after between before _46 after between before _45 after between     \
  before _44 after between before _43 after between before _42 after between before _41 after between     \
  before _40 after between before _39 after between before _38 after between before _37 after between     \
  before _36 after between before _35 after between before _34 after between before _33 after between     \
  before _32 after between before _31 after between before _30 after between before _29 after between     \
  before _28 after between before _27 after between before _26 after between before _25 after between     \
  before _24 after between before _23 after between before _22 after between before _21 after between     \
  before _20 after between before _19 after between before _18 after between before _17 after between     \
  before _16 after between before _15 after between before _14 after between before _13 after between     \
  before _12 after between before _11 after between before _10 after between before _9 after between       \
  before _8 after between before _7 after between before _6 after between before _5 after between         \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_512(before, after, between)                                                            \
  before _512 after between before _511 after between before _510 after between before _509 after between \
  before _508 after between before _507 after between before _506 after between before _505 after between \
  before _504 after between before _503 after between before _502 after between before _501 after between \
  before _500 after between before _499 after between before _498 after between before _497 after between \
  before _496 after between before _495 after between before _494 after between before _493 after between \
  before _492 after between before _491 after between before _490 after between before _489 after between \
  before _488 after between before _487 after between before _486 after between before _485 after between \
  before _484 after between before _483 after between before _482 after between before _481 after between \
  before _480 after between before _479 after between before _478 after between before _477 after between \
  before _476 after between before _475 after between before _474 after between before _473 after between \
  before _472 after between before _471 after between before _470 after between before _469 after between \
  before _468 after between before _467 after between before _466 after between before _465 after between \
  before _464 after between before _463 after between before _462 after between before _461 after between \
  before _460 after between before _459 after between before _458 after between before _457 after between \
  before _456 after between before _455 after between before _454 after between before _453 after between \
  before _452 after between before _451 after between before _450 after between before _449 after between \
  before _448 after between before _447 after between before _446 after between before _445 after between \
  before _444 after between before _443 after between before _442 after between before _441 after between \
  before _440 after between before _439 after between before _438 after between before _437 after between \
  before _436 after between before _435 after between before _434 after between before _433 after between \
  before _432 after between before _431 after between before _430 after between before _429 after between \
  before _428 after between before _427 after between before _426 after between before _425 after between \
  before _424 after between before _423 after between before _422 after between before _421 after between \
  before _420 after between before _419 after between before _418 after between before _417 after between \
  before _416 after between before _415 after between before _414 after between before _413 after between \
  before _412 after between before _411 after between before _410 after between before _409 after between \
  before _408 after between before _407 after between before _406 after between before _405 after between \
  before _404 after between before _403 after between before _402 after between before _401 after between \
  before _400 after between before _399 after between before _398 after between before _397 after between \
  before _396 after between before _395 after between before _394 after between before _393 after between \
  before _392 after between before _391 after between before _390 after between before _389 after between \
  before _388 after between before _387 after between before _386 after between before _385 after between \
  before _384 after between before _383 after between before _382 after between before _381 after between \
  before _380 after between before _379 after between before _378 after between before _377 after between \
  before _376 after between before _375 after between before _374 after between before _373 after between \
  before _372 after between before _371 after between before _370 after between before _369 after between \
  before _368 after between before _367 after between before _366 after between before _365 after between \
  before _364 after between before _363 after between before _362 after between before _361 after between \
  before _360 after between before _359 after between before _358 after between before _357 after between \
  before _356 after between before _355 after between before _354 after between before _353 after between \
  before _352 after between before _351 after between before _350 after between before _349 after between \
  before _348 after between before _347 after between before _346 after between before _345 after between \
  before _344 after between before _343 after between before _342 after between before _341 after between \
  before _340 after between before _339 after between before _338 after between before _337 after between \
  before _336 after between before _335 after between before _334 after between before _333 after between \
  before _332 after between before _331 after between before _330 after between before _329 after between \
  before _328 after between before _327 after between before _326 after between before _325 after between \
  before _324 after between before _323 after between before _322 after between before _321 after between \
  before _320 after between before _319 after between before _318 after between before _317 after between \
  before _316 after between before _315 after between before _314 after between before _313 after between \
  before _312 after between before _311 after between before _310 after between before _309 after between \
  before _308 after between before _307 after between before _306 after between before _305 after between \
  before _304 after between before _303 after between before _302 after between before _301 after between \
  before _300 after between before _299 after between before _298 after between before _297 after between \
  before _296 after between before _295 after between before _294 after between before _293 after between \
  before _292 after between before _291 after between before _290 after between before _289 after between \
  before _288 after between before _287 after between before _286 after between before _285 after between \
  before _284 after between before _283 after between before _282 after between before _281 after between \
  before _280 after between before _279 after between before _278 after between before _277 after between \
  before _276 after between before _275 after between before _274 after between before _273 after between \
  before _272 after between before _271 after between before _270 after between before _269 after between \
  before _268 after between before _267 after between before _266 after between before _265 after between \
  before _264 after between before _263 after between before _262 after between before _261 after between \
  before _260 after between before _259 after between before _258 after between before _257 after between \
  before _256 after between before _255 after between before _254 after between before _253 after between \
  before _252 after between before _251 after between before _250 after between before _249 after between \
  before _248 after between before _247 after between before _246 after between before _245 after between \
  before _244 after between before _243 after between before _242 after between before _241 after between \
  before _240 after between before _239 after between before _238 after between before _237 after between \
  before _236 after between before _235 after between before _234 after between before _233 after between \
  before _232 after between before _231 after between before _230 after between before _229 after between \
  before _228 after between before _227 after between before _226 after between before _225 after between \
  before _224 after between before _223 after between before _222 after between before _221 after between \
  before _220 after between before _219 after between before _218 after between before _217 after between \
  before _216 after between before _215 after between before _214 after between before _213 after between \
  before _212 after between before _211 after between before _210 after between before _209 after between \
  before _208 after between before _207 after between before _206 after between before _205 after between \
  before _204 after between before _203 after between before _202 after between before _201 after between \
  before _200 after between before _199 after between before _198 after between before _197 after between \
  before _196 after between before _195 after between before _194 after between before _193 after between \
  before _192 after between before _191 after between before _190 after between before _189 after between \
  before _188 after between before _187 after between before _186 after between before _185 after between \
  before _184 after between before _183 after between before _182 after between before _181 after between \
  before _180 after between before _179 after between before _178 after between before _177 after between \
  before _176 after between before _175 after between before _174 after between before _173 after between \
  before _172 after between before _171 after between before _170 after between before _169 after between \
  before _168 after between before _167 after between before _166 after between before _165 after between \
  before _164 after between before _163 after between before _162 after between before _161 after between \
  before _160 after between before _159 after between before _158 after between before _157 after between \
  before _156 after between before _155 after between before _154 after between before _153 after between \
  before _152 after between before _151 after between before _150 after between before _149 after between \
  before _148 after between before _147 after between before _146 after between before _145 after between \
  before _144 after between before _143 after between before _142 after between before _141 after between \
  before _140 after between before _139 after between before _138 after between before _137 after between \
  before _136 after between before _135 after between before _134 after between before _133 after between \
  before _132 after between before _131 after between before _130 after between before _129 after between \
  before _128 after between before _127 after between before _126 after between before _125 after between \
  before _124 after between before _123 after between before _122 after between before _121 after between \
  before _120 after between before _119 after between before _118 after between before _117 after between \
  before _116 after between before _115 after between before _114 after between before _113 after between \
  before _112 after between before _111 after between before _110 after between before _109 after between \
  before _108 after between before _107 after between before _106 after between before _105 after between \
  before _104 after between before _103 after between before _102 after between before _101 after between \
  before _100 after between before _99 after between before _98 after between before _97 after between    \
  before _96 after between before _95 after between before _94 after between before _93 after between     \
  before _92 after between before _91 after between before _90 after between before _89 after between     \
  before _88 after between before _87 after between before _86 after between before _85 after between     \
  before _84 after between before _83 after between before _82 after between before _81 after between     \
  before _80 after between before _79 after between before _78 after between before _77 after between     \
  before _76 after between before _75 after between before _74 after between before _73 after between     \
  before _72 after between before _71 after between before _70 after between before _69 after between     \
  before _68 after between before _67 after between before _66 after between before _65 after between     \
  before _64 after between before _63 after between before _62 after between before _61 after between     \
  before _60 after between before _59 after between before _58 after between before _57 after between     \
  before _56 after between before _55 after between before _54 after between before _53 after between     \
  before _52 after between before _51 after between before _50 after between before _49 after between     \
  before _48 after between before _47 after between before _46 after between before _45 after between     \
  before _44 after between before _43 after between before _42 after between before _41 after between     \
  before _40 after between before _39 after between before _38 after between before _37 after between     \
  before _36 after between before _35 after between before _34 after between before _33 after between     \
  before _32 after between before _31 after between before _30 after between before _29 after between     \
  before _28 after between before _27 after between before _26 after between before _25 after between     \
  before _24 after between before _23 after between before _22 after between before _21 after between     \
  before _20 after between before _19 after between before _18 after between before _17 after between     \
  before _16 after between before _15 after between before _14 after between before _13 after between     \
  before _12 after between before _11 after between before _10 after between before _9 after between      \
  before _8 after between before _7 after between before _6 after between before _5 after between         \
  before _4 after between before _3 after between before _2 after between before _1 after

#define JLN_MP_RXS_1024(before, after, between)                                                               \
  before _1024 after between before _1023 after between before _1022 after between before _1021 after between \
  before _1020 after between before _1019 after between before _1018 after between before _1017 after between \
  before _1016 after between before _1015 after between before _1014 after between before _1013 after between \
  before _1012 after between before _1011 after between before _1010 after between before _1009 after between \
  before _1008 after between before _1007 after between before _1006 after between before _1005 after between \
  before _1004 after between before _1003 after between before _1002 after between before _1001 after between \
  before _1000 after between before _999 after between before _998 after between before _997 after between     \
  before _996 after between before _995 after between before _994 after between before _993 after between     \
  before _992 after between before _991 after between before _990 after between before _989 after between     \
  before _988 after between before _987 after between before _986 after between before _985 after between     \
  before _984 after between before _983 after between before _982 after between before _981 after between     \
  before _980 after between before _979 after between before _978 after between before _977 after between     \
  before _976 after between before _975 after between before _974 after between before _973 after between     \
  before _972 after between before _971 after between before _970 after between before _969 after between     \
  before _968 after between before _967 after between before _966 after between before _965 after between     \
  before _964 after between before _963 after between before _962 after between before _961 after between     \
  before _960 after between before _959 after between before _958 after between before _957 after between     \
  before _956 after between before _955 after between before _954 after between before _953 after between     \
  before _952 after between before _951 after between before _950 after between before _949 after between     \
  before _948 after between before _947 after between before _946 after between before _945 after between     \
  before _944 after between before _943 after between before _942 after between before _941 after between     \
  before _940 after between before _939 after between before _938 after between before _937 after between     \
  before _936 after between before _935 after between before _934 after between before _933 after between     \
  before _932 after between before _931 after between before _930 after between before _929 after between     \
  before _928 after between before _927 after between before _926 after between before _925 after between     \
  before _924 after between before _923 after between before _922 after between before _921 after between     \
  before _920 after between before _919 after between before _918 after between before _917 after between     \
  before _916 after between before _915 after between before _914 after between before _913 after between     \
  before _912 after between before _911 after between before _910 after between before _909 after between     \
  before _908 after between before _907 after between before _906 after between before _905 after between     \
  before _904 after between before _903 after between before _902 after between before _901 after between     \
  before _900 after between before _899 after between before _898 after between before _897 after between     \
  before _896 after between before _895 after between before _894 after between before _893 after between     \
  before _892 after between before _891 after between before _890 after between before _889 after between     \
  before _888 after between before _887 after between before _886 after between before _885 after between     \
  before _884 after between before _883 after between before _882 after between before _881 after between     \
  before _880 after between before _879 after between before _878 after between before _877 after between     \
  before _876 after between before _875 after between before _874 after between before _873 after between     \
  before _872 after between before _871 after between before _870 after between before _869 after between     \
  before _868 after between before _867 after between before _866 after between before _865 after between     \
  before _864 after between before _863 after between before _862 after between before _861 after between     \
  before _860 after between before _859 after between before _858 after between before _857 after between     \
  before _856 after between before _855 after between before _854 after between before _853 after between     \
  before _852 after between before _851 after between before _850 after between before _849 after between     \
  before _848 after between before _847 after between before _846 after between before _845 after between     \
  before _844 after between before _843 after between before _842 after between before _841 after between     \
  before _840 after between before _839 after between before _838 after between before _837 after between     \
  before _836 after between before _835 after between before _834 after between before _833 after between     \
  before _832 after between before _831 after between before _830 after between before _829 after between     \
  before _828 after between before _827 after between before _826 after between before _825 after between     \
  before _824 after between before _823 after between before _822 after between before _821 after between     \
  before _820 after between before _819 after between before _818 after between before _817 after between     \
  before _816 after between before _815 after between before _814 after between before _813 after between     \
  before _812 after between before _811 after between before _810 after between before _809 after between     \
  before _808 after between before _807 after between before _806 after between before _805 after between     \
  before _804 after between before _803 after between before _802 after between before _801 after between     \
  before _800 after between before _799 after between before _798 after between before _797 after between     \
  before _796 after between before _795 after between before _794 after between before _793 after between     \
  before _792 after between before _791 after between before _790 after between before _789 after between     \
  before _788 after between before _787 after between before _786 after between before _785 after between     \
  before _784 after between before _783 after between before _782 after between before _781 after between     \
  before _780 after between before _779 after between before _778 after between before _777 after between     \
  before _776 after between before _775 after between before _774 after between before _773 after between     \
  before _772 after between before _771 after between before _770 after between before _769 after between     \
  before _768 after between before _767 after between before _766 after between before _765 after between     \
  before _764 after between before _763 after between before _762 after between before _761 after between     \
  before _760 after between before _759 after between before _758 after between before _757 after between     \
  before _756 after between before _755 after between before _754 after between before _753 after between     \
  before _752 after between before _751 after between before _750 after between before _749 after between     \
  before _748 after between before _747 after between before _746 after between before _745 after between     \
  before _744 after between before _743 after between before _742 after between before _741 after between     \
  before _740 after between before _739 after between before _738 after between before _737 after between     \
  before _736 after between before _735 after between before _734 after between before _733 after between     \
  before _732 after between before _731 after between before _730 after between before _729 after between     \
  before _728 after between before _727 after between before _726 after between before _725 after between     \
  before _724 after between before _723 after between before _722 after between before _721 after between     \
  before _720 after between before _719 after between before _718 after between before _717 after between     \
  before _716 after between before _715 after between before _714 after between before _713 after between     \
  before _712 after between before _711 after between before _710 after between before _709 after between     \
  before _708 after between before _707 after between before _706 after between before _705 after between     \
  before _704 after between before _703 after between before _702 after between before _701 after between     \
  before _700 after between before _699 after between before _698 after between before _697 after between     \
  before _696 after between before _695 after between before _694 after between before _693 after between     \
  before _692 after between before _691 after between before _690 after between before _689 after between     \
  before _688 after between before _687 after between before _686 after between before _685 after between     \
  before _684 after between before _683 after between before _682 after between before _681 after between     \
  before _680 after between before _679 after between before _678 after between before _677 after between     \
  before _676 after between before _675 after between before _674 after between before _673 after between     \
  before _672 after between before _671 after between before _670 after between before _669 after between     \
  before _668 after between before _667 after between before _666 after between before _665 after between     \
  before _664 after between before _663 after between before _662 after between before _661 after between     \
  before _660 after between before _659 after between before _658 after between before _657 after between     \
  before _656 after between before _655 after between before _654 after between before _653 after between     \
  before _652 after between before _651 after between before _650 after between before _649 after between     \
  before _648 after between before _647 after between before _646 after between before _645 after between     \
  before _644 after between before _643 after between before _642 after between before _641 after between     \
  before _640 after between before _639 after between before _638 after between before _637 after between     \
  before _636 after between before _635 after between before _634 after between before _633 after between     \
  before _632 after between before _631 after between before _630 after between before _629 after between     \
  before _628 after between before _627 after between before _626 after between before _625 after between     \
  before _624 after between before _623 after between before _622 after between before _621 after between     \
  before _620 after between before _619 after between before _618 after between before _617 after between     \
  before _616 after between before _615 after between before _614 after between before _613 after between     \
  before _612 after between before _611 after between before _610 after between before _609 after between     \
  before _608 after between before _607 after between before _606 after between before _605 after between     \
  before _604 after between before _603 after between before _602 after between before _601 after between     \
  before _600 after between before _599 after between before _598 after between before _597 after between     \
  before _596 after between before _595 after between before _594 after between before _593 after between     \
  before _592 after between before _591 after between before _590 after between before _589 after between     \
  before _588 after between before _587 after between before _586 after between before _585 after between     \
  before _584 after between before _583 after between before _582 after between before _581 after between     \
  before _580 after between before _579 after between before _578 after between before _577 after between     \
  before _576 after between before _575 after between before _574 after between before _573 after between     \
  before _572 after between before _571 after between before _570 after between before _569 after between     \
  before _568 after between before _567 after between before _566 after between before _565 after between     \
  before _564 after between before _563 after between before _562 after between before _561 after between     \
  before _560 after between before _559 after between before _558 after between before _557 after between     \
  before _556 after between before _555 after between before _554 after between before _553 after between     \
  before _552 after between before _551 after between before _550 after between before _549 after between     \
  before _548 after between before _547 after between before _546 after between before _545 after between     \
  before _544 after between before _543 after between before _542 after between before _541 after between     \
  before _540 after between before _539 after between before _538 after between before _537 after between     \
  before _536 after between before _535 after between before _534 after between before _533 after between     \
  before _532 after between before _531 after between before _530 after between before _529 after between     \
  before _528 after between before _527 after between before _526 after between before _525 after between     \
  before _524 after between before _523 after between before _522 after between before _521 after between     \
  before _520 after between before _519 after between before _518 after between before _517 after between     \
  before _516 after between before _515 after between before _514 after between before _513 after between     \
  before _512 after between before _511 after between before _510 after between before _509 after between     \
  before _508 after between before _507 after between before _506 after between before _505 after between     \
  before _504 after between before _503 after between before _502 after between before _501 after between     \
  before _500 after between before _499 after between before _498 after between before _497 after between     \
  before _496 after between before _495 after between before _494 after between before _493 after between     \
  before _492 after between before _491 after between before _490 after between before _489 after between     \
  before _488 after between before _487 after between before _486 after between before _485 after between     \
  before _484 after between before _483 after between before _482 after between before _481 after between     \
  before _480 after between before _479 after between before _478 after between before _477 after between     \
  before _476 after between before _475 after between before _474 after between before _473 after between     \
  before _472 after between before _471 after between before _470 after between before _469 after between     \
  before _468 after between before _467 after between before _466 after between before _465 after between     \
  before _464 after between before _463 after between before _462 after between before _461 after between     \
  before _460 after between before _459 after between before _458 after between before _457 after between     \
  before _456 after between before _455 after between before _454 after between before _453 after between     \
  before _452 after between before _451 after between before _450 after between before _449 after between     \
  before _448 after between before _447 after between before _446 after between before _445 after between     \
  before _444 after between before _443 after between before _442 after between before _441 after between     \
  before _440 after between before _439 after between before _438 after between before _437 after between     \
  before _436 after between before _435 after between before _434 after between before _433 after between     \
  before _432 after between before _431 after between before _430 after between before _429 after between     \
  before _428 after between before _427 after between before _426 after between before _425 after between     \
  before _424 after between before _423 after between before _422 after between before _421 after between     \
  before _420 after between before _419 after between before _418 after between before _417 after between     \
  before _416 after between before _415 after between before _414 after between before _413 after between     \
  before _412 after between before _411 after between before _410 after between before _409 after between     \
  before _408 after between before _407 after between before _406 after between before _405 after between     \
  before _404 after between before _403 after between before _402 after between before _401 after between     \
  before _400 after between before _399 after between before _398 after between before _397 after between     \
  before _396 after between before _395 after between before _394 after between before _393 after between     \
  before _392 after between before _391 after between before _390 after between before _389 after between     \
  before _388 after between before _387 after between before _386 after between before _385 after between     \
  before _384 after between before _383 after between before _382 after between before _381 after between     \
  before _380 after between before _379 after between before _378 after between before _377 after between     \
  before _376 after between before _375 after between before _374 after between before _373 after between     \
  before _372 after between before _371 after between before _370 after between before _369 after between     \
  before _368 after between before _367 after between before _366 after between before _365 after between     \
  before _364 after between before _363 after between before _362 after between before _361 after between     \
  before _360 after between before _359 after between before _358 after between before _357 after between     \
  before _356 after between before _355 after between before _354 after between before _353 after between     \
  before _352 after between before _351 after between before _350 after between before _349 after between     \
  before _348 after between before _347 after between before _346 after between before _345 after between     \
  before _344 after between before _343 after between before _342 after between before _341 after between     \
  before _340 after between before _339 after between before _338 after between before _337 after between     \
  before _336 after between before _335 after between before _334 after between before _333 after between     \
  before _332 after between before _331 after between before _330 after between before _329 after between     \
  before _328 after between before _327 after between before _326 after between before _325 after between     \
  before _324 after between before _323 after between before _322 after between before _321 after between     \
  before _320 after between before _319 after between before _318 after between before _317 after between     \
  before _316 after between before _315 after between before _314 after between before _313 after between     \
  before _312 after between before _311 after between before _310 after between before _309 after between     \
  before _308 after between before _307 after between before _306 after between before _305 after between     \
  before _304 after between before _303 after between before _302 after between before _301 after between     \
  before _300 after between before _299 after between before _298 after between before _297 after between     \
  before _296 after between before _295 after between before _294 after between before _293 after between     \
  before _292 after between before _291 after between before _290 after between before _289 after between     \
  before _288 after between before _287 after between before _286 after between before _285 after between     \
  before _284 after between before _283 after between before _282 after between before _281 after between     \
  before _280 after between before _279 after between before _278 after between before _277 after between     \
  before _276 after between before _275 after between before _274 after between before _273 after between     \
  before _272 after between before _271 after between before _270 after between before _269 after between     \
  before _268 after between before _267 after between before _266 after between before _265 after between     \
  before _264 after between before _263 after between before _262 after between before _261 after between     \
  before _260 after between before _259 after between before _258 after between before _257 after between     \
  before _256 after between before _255 after between before _254 after between before _253 after between     \
  before _252 after between before _251 after between before _250 after between before _249 after between     \
  before _248 after between before _247 after between before _246 after between before _245 after between     \
  before _244 after between before _243 after between before _242 after between before _241 after between     \
  before _240 after between before _239 after between before _238 after between before _237 after between     \
  before _236 after between before _235 after between before _234 after between before _233 after between     \
  before _232 after between before _231 after between before _230 after between before _229 after between     \
  before _228 after between before _227 after between before _226 after between before _225 after between     \
  before _224 after between before _223 after between before _222 after between before _221 after between     \
  before _220 after between before _219 after between before _218 after between before _217 after between     \
  before _216 after between before _215 after between before _214 after between before _213 after between     \
  before _212 after between before _211 after between before _210 after between before _209 after between     \
  before _208 after between before _207 after between before _206 after between before _205 after between     \
  before _204 after between before _203 after between before _202 after between before _201 after between     \
  before _200 after between before _199 after between before _198 after between before _197 after between     \
  before _196 after between before _195 after between before _194 after between before _193 after between     \
  before _192 after between before _191 after between before _190 after between before _189 after between     \
  before _188 after between before _187 after between before _186 after between before _185 after between     \
  before _184 after between before _183 after between before _182 after between before _181 after between     \
  before _180 after between before _179 after between before _178 after between before _177 after between     \
  before _176 after between before _175 after between before _174 after between before _173 after between     \
  before _172 after between before _171 after between before _170 after between before _169 after between     \
  before _168 after between before _167 after between before _166 after between before _165 after between     \
  before _164 after between before _163 after between before _162 after between before _161 after between     \
  before _160 after between before _159 after between before _158 after between before _157 after between     \
  before _156 after between before _155 after between before _154 after between before _153 after between     \
  before _152 after between before _151 after between before _150 after between before _149 after between     \
  before _148 after between before _147 after between before _146 after between before _145 after between     \
  before _144 after between before _143 after between before _142 after between before _141 after between     \
  before _140 after between before _139 after between before _138 after between before _137 after between     \
  before _136 after between before _135 after between before _134 after between before _133 after between     \
  before _132 after between before _131 after between before _130 after between before _129 after between     \
  before _128 after between before _127 after between before _126 after between before _125 after between     \
  before _124 after between before _123 after between before _122 after between before _121 after between     \
  before _120 after between before _119 after between before _118 after between before _117 after between     \
  before _116 after between before _115 after between before _114 after between before _113 after between     \
  before _112 after between before _111 after between before _110 after between before _109 after between     \
  before _108 after between before _107 after between before _106 after between before _105 after between     \
  before _104 after between before _103 after between before _102 after between before _101 after between     \
  before _100 after between before _99 after between before _98 after between before _97 after between         \
  before _96 after between before _95 after between before _94 after between before _93 after between         \
  before _92 after between before _91 after between before _90 after between before _89 after between         \
  before _88 after between before _87 after between before _86 after between before _85 after between         \
  before _84 after between before _83 after between before _82 after between before _81 after between         \
  before _80 after between before _79 after between before _78 after between before _77 after between         \
  before _76 after between before _75 after between before _74 after between before _73 after between         \
  before _72 after between before _71 after between before _70 after between before _69 after between         \
  before _68 after between before _67 after between before _66 after between before _65 after between         \
  before _64 after between before _63 after between before _62 after between before _61 after between         \
  before _60 after between before _59 after between before _58 after between before _57 after between         \
  before _56 after between before _55 after between before _54 after between before _53 after between         \
  before _52 after between before _51 after between before _50 after between before _49 after between         \
  before _48 after between before _47 after between before _46 after between before _45 after between         \
  before _44 after between before _43 after between before _42 after between before _41 after between         \
  before _40 after between before _39 after between before _38 after between before _37 after between         \
  before _36 after between before _35 after between before _34 after between before _33 after between         \
  before _32 after between before _31 after between before _30 after between before _29 after between         \
  before _28 after between before _27 after between before _26 after between before _25 after between         \
  before _24 after between before _23 after between before _22 after between before _21 after between         \
  before _20 after between before _19 after between before _18 after between before _17 after between         \
  before _16 after between before _15 after between before _14 after between before _13 after between         \
  before _12 after between before _11 after between before _10 after between before _9 after between           \
  before _8 after between before _7 after between before _6 after between before _5 after between             \
  before _4 after between before _3 after between before _2 after between before _1 after

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _fold_left;
  }

  template<class F, class C = identity>
  struct fold_left
  {
    template<class state, class... xs>
    using f = typename C::template f<
      typename detail::_fold_left<
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))
      >::template f<F::template f, state, xs...>
    >;
  };

  namespace emp
  {
    template<class L, class state, class C = mp::identity>
    using fold_left = unpack<L,
      mp::push_front<state, mp::fold_left<C>>>;
  }
}


namespace jln::mp::detail
{
#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct _fold_left<n>                                \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),         \
      class... xs>                                    \
    using f = typename _fold_left<                    \
      detail::n_4_or_less_8_16_64_256(sizeof...(xs))  \
    >::template f<F,                                  \
      mp_dup(F<, JLN_MP_NIL) state,                   \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA), xs...       \
    >;                                                \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

#define JLN_MP_FOLD_LEFT_SELECT(n, mp_xs, _, mp_dup)  \
  template<>                                          \
  struct _fold_left<n>                                \
  {                                                   \
    template<template<class...> class F, class state, \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>         \
    using f = mp_dup(F<, JLN_MP_NIL) state,           \
      mp_xs(JLN_MP_NIL, >, JLN_MP_COMMA);             \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_LEFT_SELECT)

#undef JLN_MP_FOLD_LEFT_SELECT

  template<>
  struct _fold_left<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };
}
namespace jln::mp
{
  template<template<class...> class source, class error>
  class error_occurred
  {
    template<class new_error>
    using next = error_occurred<source, new_error>;
  };

  namespace err
  {
    class all_parameters_must_be_of_type_mp_list;

    class not_a_number;

    class you_need_to_add_a_specialization;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<std::size_t n JLN_MP_DEBUG_A(class = err::all_parameters_must_be_of_type_mp_list)>
    struct _join_select;
  }

  template<class C = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>::template f<C, seqs...>::type;
  };

  namespace emp
  {
    template<class... seqs>
    using join = mp::call<mp::join<>, seqs...>;
  }
}

namespace jln::mp::detail
{
  template<std::size_t n JLN_MP_DEBUG_A(class error)>
  struct _join_select : _join_select<n_16_64_256_1024(n)>
  {};

#define JLN_MP_JOIN_SELECT(n, mp_xs, mp_rxs, _)             \
  template<JLN_MP_DEBUG(class error)>                       \
  struct _join_select<n JLN_MP_DEBUG_A(error)>              \
  {                                                         \
    template<class F,                    \
      mp_xs(class, = list<>, JLN_MP_COMMA)>                 \
    struct f;                                               \
                                                            \
    template<class F,                    \
      mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>            \
    struct f<F, mp_xs(list<, ...>, JLN_MP_COMMA)>           \
    {                                                       \
      using type = typename F::template f<mp_xs(JLN_MP_NIL, ..., JLN_MP_COMMA)>; \
    };                                                      \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_JOIN_SELECT)

#undef JLN_MP_JOIN_SELECT

  template<JLN_MP_DEBUG(class error)>
  struct _join_select<1024 JLN_MP_DEBUG_A(error)>
  {
    template<class F,
      JLN_MP_XS_1024(class, = list<>, JLN_MP_COMMA),
      class... tail>
    struct f;

    template<class F,
      JLN_MP_XS_1024(class..., JLN_MP_NIL, JLN_MP_COMMA),
      class... tail>
    struct f<F, JLN_MP_XS_1024(list<, ...>, JLN_MP_COMMA), tail...>
    : _join_select<sizeof...(tail)+1>
    ::template f<F, list<JLN_MP_XS_1024(JLN_MP_NIL, ..., JLN_MP_COMMA)>, tail...>
    {};
  };
} // namespace jln::mp::detail
namespace jln::mp
{
  template<class F, class C = identity>
  struct accumulate
  {
    template<class state, class... seqs>
    using f = call<join<push_front<state, fold_left<F, C>>>, seqs...>;
  };

  namespace emp
  {
    template<class L, class state, class F, class C = mp::identity>
    using accumulate = unpack<L,
      mp::push_front<state, mp::accumulate<F, C>>>;
  }
}
namespace jln::mp
{
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = dispatch<C, F, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = unpack<L, mp::transform<C>>;
  }
}


namespace jln::mp::detail
{
  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
namespace jln::mp
{
  template<bool>
  struct conditional_c
  {
    template<class x, class y>
    using f = x;
  };

  template<>
  struct conditional_c<false>
  {
    template<class x, class y>
    using f = y;
  };

  template<class v>
  using conditional = conditional_c<bool(v::value)>;

  namespace emp
  {
    template<class v, class x, class y>
    using conditional = typename mp::conditional_c<bool(v::value)>
      ::template f<x, y>;

    template<bool cond, class x, class y>
    using conditional_c = typename mp::conditional_c<cond>
      ::template f<x, y>;
  }
} // namespace jln::mp
namespace jln::mp
{
  template<class x, class C = identity>
  struct always
  {
    template<class... xs>
    using f = typename C::template f<x>;
  };
}
namespace jln::mp
{
  using int_ = std::intmax_t;

  template<int_ v>
  struct number { static const int_ value = v; };

  using true_ = number<1>;
  using false_ = number<0>;
}
namespace jln::mp
{
  template<class Pred, class TC, class FC = always<false_>>
  struct if_
  {
    template<class... xs>
    using f = typename mp::conditional_c<bool(call<Pred, xs...>::value)>
      ::template f<TC, FC>
      ::template f<xs...>;
  };

  namespace emp
  {
    template<class Pred, class TC, class FC, class... xs>
    using if_ = typename conditional<call<Pred, xs...>, TC, FC>
      ::template f<xs...>;
  }
}
namespace jln::mp
{
  template<class T, class C = listify>
  struct push_back
  {
    template<class... xs>
    using f = call<C, xs..., T>;
  };

  namespace emp
  {
    template<class L, class T, class C = mp::listify>
    using push_back = unpack<L, mp::push_back<T, C>>;
  }
}
namespace jln::mp
{
  template<class C = identity>
  struct size
  {
    template<class... xs>
    using f = typename C::template f<number<sizeof...(xs)>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using size = unpack<L, mp::size<C>>;
  }
}
/**
* \author    Jonathan Poelen <jonathan.poelen+jln@gmail.com>
* \version   0.1
* \brief     C++17 utility macros
*/

#define JLN_PRAGMA(x) JLN_PRAGMA_I(x)

#ifdef _MSC_VER
#  define JLN_PRAGMA_I(x) __pragma(x)
#else
#  define JLN_PRAGMA_I(x) _Pragma(#x)
#endif


// Diagnostic
//@{
#ifdef _MSC_VER

#  define JLN_DIAGNOSTIC_PUSH __pragma(warning(push))
#  define JLN_DIAGNOSTIC_POP __pragma(warning(pop))

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X) __pragma(warning(disable:X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_DIAGNOSTIC_MSVC_WARNING(X) __pragma(warning(4:X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_DIAGNOSTIC_MSVC_ERROR(X) __pragma(error(X))
#  define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_DIAGNOSTIC_CLANG_ERROR(X)

#elif defined(__GNUC__) || defined(__clang__)

#  define JLN_DIAGNOSTIC_PUSH JLN_PRAGMA(GCC diagnostic push)
#  define JLN_DIAGNOSTIC_POP JLN_PRAGMA(GCC diagnostic pop)

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X) JLN_PRAGMA(GCC diagnostic ignored X)
#  define JLN_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X) JLN_PRAGMA(GCC diagnostic warning X)
#  define JLN_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X) JLN_PRAGMA(GCC diagnostic error X)
#  ifdef __clang__
#    define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#    define JLN_DIAGNOSTIC_CLANG_IGNORE JLN_DIAGNOSTIC_GCC_IGNORE
#    define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#    define JLN_DIAGNOSTIC_CLANG_WARNING JLN_DIAGNOSTIC_GCC_WARNING
#    define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#    define JLN_DIAGNOSTIC_CLANG_ERROR JLN_DIAGNOSTIC_GCC_ERROR
#  else
#    define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE JLN_DIAGNOSTIC_GCC_IGNORE
#    define JLN_DIAGNOSTIC_CLANG_IGNORE(X)
#    define JLN_DIAGNOSTIC_GCC_ONLY_WARNING JLN_DIAGNOSTIC_GCC_WARNING
#    define JLN_DIAGNOSTIC_CLANG_WARNING(X)
#    define JLN_DIAGNOSTIC_GCC_ONLY_ERROR JLN_DIAGNOSTIC_GCC_ERROR
#    define JLN_DIAGNOSTIC_CLANG_ERROR(X)
#  endif

#else

#  define JLN_DIAGNOSTIC_PUSH
#  define JLN_DIAGNOSTIC_POP

#  define JLN_DIAGNOSTIC_MSVC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_IGNORE(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_IGNORE(X)
#  define JLN_DIAGNOSTIC_CLANG_IGNORE(X)

#  define JLN_DIAGNOSTIC_MSVC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_WARNING(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_WARNING(X)
#  define JLN_DIAGNOSTIC_CLANG_WARNING(X)

#  define JLN_DIAGNOSTIC_MSVC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ERROR(X)
#  define JLN_DIAGNOSTIC_GCC_ONLY_ERROR(X)
#  define JLN_DIAGNOSTIC_CLANG_ERROR(X)

#endif

//@}
JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  template<class C = identity>
  struct or_
  {
    template<class... xs>
    using f = typename C::template f<number<(false || ... || xs::value)>>;
  };

  template<class C = identity>
  struct and_
  {
    template<class... xs>
    using f = typename C::template f<number<(true && ... && xs::value)>>;
  };

  template<class C = identity>
  struct add
  {
    template<class... xs>
    using f = typename C::template f<number<(... + xs::value)>>;
  };

  template<class C = identity>
  using add0 = if_<size<>, add<C>, always<number<0>, C>>;

  template<class C = identity>
  struct sub
  {
    template<class... xs>
    using f = typename C::template f<number<(... - xs::value)>>;
  };

  template<class C = identity>
  using sub0 = if_<size<>, sub<C>, always<number<0>, C>>;

  template<class C = identity>
  struct lshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... << xs::value)>>;
  };

  template<class C = identity>
  using lshift0 = if_<size<>, lshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct rshift
  {
    template<class... xs>
    using f = typename C::template f<number<(... >> xs::value)>>;
  };

  template<class C = identity>
  using rshift0 = if_<size<>, rshift<C>, always<number<0>, C>>;

  template<class C = identity>
  struct mul
  {
    template<class... xs>
    using f = typename C::template f<number<(... * xs::value)>>;
  };

  template<class C = identity>
  using mul0 = if_<size<>, mul<C>, always<number<0>, C>>;

  template<class C = identity>
  using mul1 = if_<size<>, mul<C>, always<number<1>, C>>;

  template<class C = identity>
  struct div
  {
    template<class... xs>
    using f = typename C::template f<number<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0 = if_<size<>, div<C>, always<number<0>, C>>;

  template<class C = identity>
  using div1 = if_<size<>, div<C>, always<number<1>, C>>;

  template<class C = identity>
  struct mod
  {
    template<class... xs>
    using f = typename C::template f<number<(... %  xs::value)>>;
  };

  template<class C = identity>
  using mod0 = if_<size<>, mod<C>, always<number<0>, C>>;

  template<class C = identity>
  using mod1 = if_<size<>, mod<C>, always<number<1>, C>>;

  template<class C = identity>
  struct xor_
  {
    template<class... xs>
    using f = typename C::template f<number<(... ^ xs::value)>>;
  };

  template<class C = identity>
  using xor0 = if_<size<>, xor_<C>, always<number<0>, C>>;

  template<class C = identity>
  struct bit_and
  {
    template<class... xs>
    using f = typename C::template f<number<(... & xs::value)>>;
  };

  template<class C = identity>
  using bit_and0 = if_<size<>, bit_and<C>, always<number<0>, C>>;

  template<class C = identity>
  struct bit_or
  {
    template<class... xs>
    using f = typename C::template f<number<(... | xs::value)>>;
  };

  template<class C = identity>
  using bit_or0 = if_<size<>, bit_or<C>, always<number<0>, C>>;

  template<class C = identity>
  struct neg
  {
    template<class x>
    using f = typename C::template f<number<(-x::value)>>;
  };

  template<class C = identity>
  struct unary_plus
  {
    template<class x>
    using f = typename C::template f<number<(+x::value)>>;
  };

  template<class C = identity>
  struct not_
  {
    template<class x>
    using f = typename C::template f<number<(!x::value)>>;
  };

  template<class C = identity>
  struct bit_not
  {
    template<class x>
    using f = typename C::template f<number<(~x::value)>>;
  };

  template<class C = identity>
  struct inc
  {
    template<class x>
    using f = typename C::template f<number<(x::value+1)>>;
  };

  template<class C = identity>
  struct dec
  {
    template<class x>
    using f = typename C::template f<number<(x::value-1)>>;
  };

  template<class C = identity>
  struct equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value == y::value)>>;
  };

  template<class C = identity>
  struct not_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value != y::value)>>;
  };

  template<class C = identity>
  struct less
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value < y::value)>>;
  };

  template<class C = identity>
  struct less_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value <= y::value)>>;
  };

  template<class C = identity>
  struct greater
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value > y::value)>>;
  };

  template<class C = identity>
  struct greater_equal
  {
    template<class x, class y>
    using f = typename C::template f<number<(x::value >= y::value)>>;
  };


  template<class N, class C = identity>
  using equal_than = push_back<N, equal<C>>;

  template<class N, class C = identity>
  using not_equal_than = push_back<N, not_equal<C>>;

  template<class N, class C = identity>
  using less_than = push_back<N, less<C>>;

  template<class N, class C = identity>
  using less_equal_than = push_back<N, less_equal<C>>;

  template<class N, class C = identity>
  using greater_than = push_back<N, greater<C>>;

  template<class N, class C = identity>
  using greater_equal_than = push_back<N, greater_equal<C>>;


  template<int_ n, class C = identity>
  using equal_than_c = equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_than_c = not_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq = unpack<L, mp::or_<C>>;

  template<class L, class C = mp::identity>
  using and_seq = unpack<L, mp::and_<C>>;

  template<class L, class C = mp::identity>
  using add_seq = unpack<L, mp::add<C>>;

  template<class L, class C = mp::identity>
  using add0_seq = unpack<L, mp::add0<C>>;

  template<class L, class C = mp::identity>
  using sub_seq = unpack<L, mp::sub<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq = unpack<L, mp::sub0<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq = unpack<L, mp::lshift<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq = unpack<L, mp::lshift0<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq = unpack<L, mp::rshift<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq = unpack<L, mp::rshift0<C>>;

  template<class L, class C = mp::identity>
  using mul_seq = unpack<L, mp::mul<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq = unpack<L, mp::mul0<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq = unpack<L, mp::mul1<C>>;

  template<class L, class C = mp::identity>
  using div_seq = unpack<L, mp::div<C>>;

  template<class L, class C = mp::identity>
  using div0_seq = unpack<L, mp::div0<C>>;

  template<class L, class C = mp::identity>
  using div1_seq = unpack<L, mp::div1<C>>;

  template<class L, class C = mp::identity>
  using mod_seq = unpack<L, mp::mod<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq = unpack<L, mp::mod0<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq = unpack<L, mp::mod1<C>>;

  template<class L, class C = mp::identity>
  using xor_seq = unpack<L, mp::xor_<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq = unpack<L, mp::xor0<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq = unpack<L, mp::bit_and<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq = unpack<L, mp::bit_and0<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq = unpack<L, mp::bit_or<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq = unpack<L, mp::bit_or0<C>>;


  template<int_... xs>
  using or_c = number<(false || ... || xs)>;

  template<int_... xs>
  using and_c = number<(true && ... && xs)>;

  template<int_... xs>
  using add_c = number<(... + xs)>;

  template<int_... xs>
  using add0_c = add_c<xs..., 0>;

  template<int_... xs>
  using sub_c = number<(... - xs)>;

  template<int_... xs>
  using sub0_c = sub_c<xs..., 0>;

  template<int_... xs>
  using lshift_c = number<(... << xs)>;

  template<int_... xs>
  using lshift0_c = lshift_c<xs..., 0>;

  template<int_... xs>
  using rshift_c = number<(... >> xs)>;

  template<int_... xs>
  using rshift0_c = rshift_c<xs..., 0>;

  template<int_... xs>
  using mul_c = number<(... * xs)>;

  template<int_... xs>
  using mul0_c = mul_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using mul1_c = mul_c<xs..., 1>;

  template<int_... xs>
  using div_c = number<(... / xs)>;

  template<int_... xs>
  using div0_c = div_c<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<int_... xs>
  using div1_c = div_c<xs..., 1>;

  template<int_... xs>
  using mod_c = number<(... % xs)>;

  template<int_... xs>
  using mod0_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 0)>;

  template<int_... xs>
  using mod1_c = mod_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::min() : 1)>;

  template<int_... xs>
  using xor_c = number<(... ^ xs)>;

  template<int_... xs>
  using xor0_c = xor_c<xs..., 0, 0>;

  template<int_... xs>
  using bit_and_c = number<(... & xs)>;

  template<int_... xs>
  using bit_and0_c = bit_and_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;

  template<int_... xs>
  using bit_or_c = number<(... | xs)>;

  template<int_... xs>
  using bit_or0_c = bit_or_c<xs...,
    (sizeof...(xs) ? std::numeric_limits<int_>::max() : 0)>;


  template<class... xs>
  using or_ = number<(false || ... || xs::value)>;

  template<class... xs>
  using and_ = number<(true && ... && xs::value)>;

  template<class... xs>
  using add = number<(... + xs::value)>;

  template<class... xs>
  using add0 = call<mp::add0<>, xs...>;

  template<class... xs>
  using sub = number<(... - xs::value)>;

  template<class... xs>
  using sub0 = call<mp::sub0<>, xs...>;

  template<class... xs>
  using lshift = number<(... << xs::value)>;

  template<class... xs>
  using lshift0 = call<mp::lshift0<>, xs...>;

  template<class... xs>
  using rshift = number<(... >> xs::value)>;

  template<class... xs>
  using rshift0 = call<mp::rshift0<>, xs...>;

  template<class... xs>
  using mul = number<(... * xs::value)>;

  template<class... xs>
  using mul0 = call<mp::mul0<>, xs...>;

  template<class... xs>
  using mul1 = call<mp::mul1<>, xs...>;

  template<class... xs>
  using div = number<(... / xs::value)>;

  template<class... xs>
  using div0 = call<mp::div0<>, xs...>;

  template<class... xs>
  using div1 = call<mp::div1<>, xs...>;

  template<class... xs>
  using mod = number<(... % xs::value)>;

  template<class... xs>
  using mod0 = call<mp::mod0<>, xs...>;

  template<class... xs>
  using mod1 = call<mp::mod1<>, xs...>;

  template<class... xs>
  using xor_ = number<(... ^ xs::value)>;

  template<class... xs>
  using xor0 = call<mp::xor0<>, xs...>;

  template<class... xs>
  using bit_and = number<(... & xs::value)>;

  template<class... xs>
  using bit_and0 = call<mp::bit_and0<>, xs...>;

  template<class... xs>
  using bit_or = number<(... | xs::value)>;

  template<class... xs>
  using bit_or0 = call<mp::bit_or0<>, xs...>;


  template<class x, class C = mp::identity>
  using neg = call<mp::neg<C>, x>;

  template<class x, class C = mp::identity>
  using unary_plus = call<mp::unary_plus<C>, x>;

  template<class x, class C = mp::identity>
  using not_ = call<mp::not_<C>, x>;

  template<class x, class C = mp::identity>
  using bit_not = call<mp::bit_not<C>, x>;

  template<class x, class C = mp::identity>
  using inc = call<mp::inc<C>, x>;

  template<class x, class C = mp::identity>
  using dec = call<mp::dec<C>, x>;

  template<class x, class y, class C = mp::identity>
  using equal = call<mp::equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal = call<mp::not_equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less = call<mp::less<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal = call<mp::less_equal<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater = call<mp::greater<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal = call<mp::greater_equal<C>, x, y>;
}

JLN_DIAGNOSTIC_POP
namespace jln::mp
{
  template<class Pred, class C = identity>
  using all_of = transform<Pred, and_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using all_of = unpack<L, mp::all_of<Pred, C>>;
  }
} // namespace jln::mp
namespace jln::mp
{
  template<class Pred, class C = identity>
  using any_of = transform<Pred, or_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using any_of = unpack<L, mp::any_of<Pred, C>>;
  }
} // namespace jln::mp
namespace jln::mp
{
  namespace detail
  {
    template<class, unsigned>
    struct _cartesian;
  }

  template<class C = listify>
  struct cartesian
  {
    template<class... seqs>
    using f = typename detail::_cartesian<C, detail::min(2, sizeof...(seqs))>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using cartesian = unpack<L, cartesian<C>>;
  }
}


namespace jln::mp::detail
{
  template<class, class>
  struct _product;

  template<class... xs, class... ys>
  struct _product<list<xs...>, list<ys...>>
  {
    using type = list<list<xs..., ys>...>;
  };

  template<class... ys>
  struct _product<list<>, list<ys...>>
  {
    using type = list<>;
  };

  template<class>
  struct _product1;

  template<class... xs>
  struct _product1<list<xs...>>
  {
    using type = list<list<xs>...>;
  };

  template<class C>
  struct _cartesian<C, 0>
  {
    template<class...>
    using f = typename C::template f<>;
  };

  template<>
  struct _cartesian<listify, 0>
  {
    template<class...>
    using f = list<>;
  };

  template<class C>
  struct _cartesian<C, 1>
  {
    template<class seq>
    using f = typename C::template f<
      typename _product1<seq>::type>;
  };

  template<>
  struct _cartesian<listify, 1>
  {
    template<class seq>
    using f = typename _product1<seq>::type;
  };

  template<class, class>
  struct _cartesian_impl;

  template<class... seqs, class seq>
  struct _cartesian_impl<list<seqs...>, seq>
  {
    using type = typename join<>
      ::f<typename _product<seqs, seq>::type...>;
  };

  template<class C, unsigned n>
  struct _cartesian
  {
    template<class seq, class... seqs>
    using f = typename fold_left<cfl<detail::_cartesian_impl>, unpack<C>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };

  template<unsigned n>
  struct _cartesian<listify, n>
  {
    template<class seq, class... seqs>
    using f = typename fold_left<cfl<detail::_cartesian_impl>>
      ::template f<typename _product1<seq>::type, seqs...>;
  };
}
namespace jln::mp
{
  template<class C = listify>
  struct numbers
  {
    template<int_... ns>
    using f = call<C, number<ns>...>;
  };

  template<>
  struct numbers<listify>
  {
    template<int_... ns>
    using f = list<number<ns>...>;
  };

  namespace emp
  {
    template<int_... vs>
    using numbers = list<number<vs>...>;
  }
}
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


namespace jln::mp
{
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<std::size_t>
#else
    template<class>
#endif
    struct _make_int_sequence;
  }

  template<class C = numbers<>>
  struct make_int_sequence_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    using f = typename detail::_make_int_sequence<n::value>
      ::type::template f<C>;
#else
    using f = typename detail::_make_int_sequence<
      std::make_index_sequence<n::value>>::template f<C>;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  namespace emp
  {
    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename mp::make_int_sequence_v<C>::template f<n>;

    template<int_ n, class C = mp::numbers<>>
    using make_int_sequence_v_c = make_int_sequence_v<mp::number<n>, C>;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename mp::make_int_sequence<C>::template f<n>;

    template<int_ n, class C = mp::listify>
    using make_int_sequence_c = make_int_sequence<mp::number<n>, C>;
  }
} // namespace jln::mp

namespace jln::mp::detail
{
#if JLN_MP_USE_MAKE_INTEGER_SEQ
  template<class, int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = __make_integer_seq<_make_int_sequence_impl, int_, n>;
  };
#elif JLN_MP_USE_INTEGER_PACK
  template<int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = _make_int_sequence_impl<__integer_pack(n)...>;
  };
#else
  template<std::size_t... ns>
  struct _make_int_sequence<std::integer_sequence<std::size_t, ns...>>
  {
    template<class C>
    using f = typename C::template f<int_(ns)...>;
  };
#endif
}

#undef JLN_MP_USE_INTEGER_PACK
#undef JLN_MP_USE_MAKE_INTEGER_SEQ

#if 0
namespace jln::mp::emp
{
  template<int_ n, class C = listify>
  using make_int_sequence_c = typename _make_int_sequence<
    (n == 0 ? 0 : n == 1 ? -1 : n-1)
  >::template f<jln::mp::numbers<C>>;
}

namespace jln::mp::detail
{
  template<int_...>
  class enumeration;

  template<bool, int_ n, class ns>
  struct _make_int_sequence_impl;

  template<int_ n, int_... ns>
  struct _make_int_sequence_impl<false, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)...>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)...>;
  };

  template<int_ n, int_... ns>
  struct _make_int_sequence_impl<true, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)..., n*2+1>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)..., n*2+1>;
  };

  template<int_ n>
  struct _make_int_sequence
 : _make_int_sequence_impl<bool(n & 1), n/2, typename _make_int_sequence<n / 2>::type>
  {};

  template<>
  struct _make_int_sequence<0>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _make_int_sequence<-1>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<0>;
  };
}
#endif
namespace jln::mp
{
  namespace detail
  {
    template<int_ n>
    struct _repeat;
  }

  template<class N, class C = listify>
  struct repeat
  {
    template<class... xs>
    using f = emp::make_int_sequence<N,
      typename detail::_repeat<detail::min(sizeof...(xs), 2)>
        ::template f<C, xs...>>;
  };

  template<int_ n, class C = listify>
  using repeat_c = repeat<number<n>, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = unpack<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = unpack<L, mp::repeat<number<n>, C>>;
  }
}


namespace jln::mp::detail
{
  template<>
  struct _repeat<0>
  {
    template<class C>
    using f = _cartesian<C, 0>; // for C::f<>
  };

  template<>
  struct _repeat<1>
  {
    template<class C, class x>
    using f = transform<always<x>, C>;
  };

  template<>
  struct _repeat<2>
  {
    template<class C, class... xs>
    using f = transform<always<list<xs...>>, join<C>>;
  };
}
namespace jln::mp
{
  template<class C = listify>
  struct combine
  {
    template<class... xs>
    using f = typename repeat_c<sizeof...(xs), cartesian<C>>
      ::template f<list<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using combine = unpack<L, mp::combine<C>>;
  }
}
namespace jln::mp
{
  template <class T, class C = identity>
  struct same_as
  {
    template <class x>
    using f = typename C::template f<number<std::is_same<T, x>::value>>;
  };
} // namespace jln::mp
namespace jln::mp
{
  template<class x, class C = identity>
  using contains = any_of<same_as<x>, C>;
  // using contains = find<x, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class L, class x, class C = mp::identity>
    using contains = unpack<L, mp::contains<x, C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class Pred>
    struct mk_list_wrap_if;

    template<class Pred>
    struct mk_list_wrap_if_not;

    template<bool>
    struct _list_wrap_if_c;
  }

  template<class Pred>
  using list_wrap_if = typename detail::mk_list_wrap_if<Pred>::type;

  template<class Pred>
  using list_wrap_if_not = typename detail::mk_list_wrap_if_not<Pred>::type;

  template<bool b>
  using list_wrap_if_c = detail::_list_wrap_if_c<b>;

  namespace emp
  {
    template<class Pred, class... xs>
    using list_wrap_if = typename mp::list_wrap_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using list_wrap_if_not = typename mp::list_wrap_if_not<Pred>::template f<xs...>;

    template<bool b, class... xs>
    using list_wrap_if_c = typename mp::list_wrap_if_c<b>::template f<xs...>;
  }
}

namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _same;
  }

  template<class C = identity>
  struct same
  {
    template<class... xs>
    using f = typename C::template f<
      typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>>;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using same = unpack<L, mp::same<C>>;
  }
}


namespace jln::mp
{
  template<>
  struct same<identity>
  {
    template<class... xs>
    using f = typename detail::_same<detail::min(sizeof...(xs), 3)>::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<>
  struct _same<0>
  {
    template<class...>
    using f = mp::true_;
  };

  template<>
  struct _same<1>
  {
    template<class>
    using f = mp::true_;
  };

  template<>
  struct _same<2>
  {
    template<class x, class y>
    using f = mp::number<std::is_same<x, y>::value>;
  };

  template<>
  struct _same<3>
  {
    template<class x, class... xs>
    using f = mp::number<std::is_same<list<x, xs...>, list<xs..., x>>::value>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template <unsigned n>
    struct _rotate;

    constexpr unsigned _rotate_size(int_ n, unsigned size)
    {
      return n >= size
        ? (size ? n % size : 0)
        : (n < 0 ? (size && n % size ? size + n % size : 0) : n);
    }
  }

  template <class N, class C = listify>
  struct rotate
  {
    template<class... xs>
    using f = typename detail::_rotate<detail::n_8_or_less_16_64_256(
      detail::_rotate_size(N::value, sizeof...(xs))
    )>
    ::template f<
      detail::_rotate_size(N::value, sizeof...(xs)),
      C, xs...
    >;
  };

  template <int_ n, class C = listify>
  using rotate_c = rotate<number<n>, C>;

  namespace emp
  {
    template <class L, class n, class C = mp::listify>
    using rotate = unpack<L, mp::rotate<n, C>>;

    template <class L, int_ n, class C = mp::listify>
    using rotate_c = unpack<L, mp::rotate<number<n>, C>>;
  }
}


namespace jln::mp::detail
{
#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, _)           \
  template<>                                              \
  struct _rotate<n>                                       \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename C::template f<                     \
      xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL

#define JLN_MP_ROTATE_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  JLN_MP_ROTATE_IMPL2(n, mp_xs, mp_rep, mp_rxs,      \
    n_8_or_less_16_64_256)

#define JLN_MP_ROTATE_IMPL2(n, mp_xs, mp_rxs, _, next_int) \
  template<>                                               \
  struct _rotate<n>                                        \
  {                                                        \
    template<unsigned size, class C,                       \
      mp_xs(class, JLN_MP_COMMA, JLN_MP_NIL)               \
      class... xs>                                         \
    using f = typename _rotate<next_int (size-n)>          \
      ::template f<size-n, C,                              \
        xs... mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)  \
      >;                                                   \
  };

  JLN_MP_GEN_XS_8_args(JLN_MP_ROTATE_IMPL2, JLN_MP_NIL)
  JLN_MP_GEN_XS_16_64_256(JLN_MP_ROTATE_IMPL)

#undef JLN_MP_ROTATE_IMPL2
#undef JLN_MP_ROTATE_IMPL
} // namespace jln::mp
namespace jln::mp
{
  namespace detail
  {
    template <class C, class... Fs>
    struct _fork;
  }

  // TODO DOXY template<class... F, class C>
  template <class... Fs>
  struct fork
  : rotate<number<-1>, cfe<detail::_fork>>
  ::template f<Fs...>
  {};

  template <class F, class C>
  struct fork<F, C>
  {
    template<class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct fork<F0, F1, C>
  {
    template<class... xs>
    using f = binary_compose_call<C, F0, F1, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct fork<F0, F1, F2, C>
  {
    template<class... xs>
    using f = ternary_compose_call<C, F0, F1, F2, xs...>;
  };
}

namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _fork
  {
    template <class... xs>
    using f = typename C::template f<call<Fs, xs...>...>;
  };
} // namespace jln::mp
namespace jln::mp::detail
{
  template<>
  struct _list_wrap_if_c<false>
  {
    template<class>
    using f = list<>;
  };

  template<>
  struct _list_wrap_if_c<true>
  {
    template<class x>
    using f = list<x>;
  };


  template<class Pred>
  struct _list_wrap_if
  {
    template<class x, class... xs>
    using f = typename _list_wrap_if_c<call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_list_wrap_if
  {
    using type = _list_wrap_if<Pred>;
  };

  template<class x, class C>
  struct mk_list_wrap_if<same_as<x, not_<C>>>
  : mk_list_wrap_if_not<same_as<x, C>>
  {};

  template<class C>
  struct mk_list_wrap_if<same<not_<C>>>
  : mk_list_wrap_if_not<same<C>>
  {};

  template<class C>
  struct mk_list_wrap_if<not_<C>>
  : mk_list_wrap_if_not<C>
  {};

  template<class Pred>
  struct mk_list_wrap_if<fork<Pred, not_<>>>
  : mk_list_wrap_if_not<Pred>
  {};


  template<class Pred>
  struct _list_wrap_if_not
  {
    template<class x, class... xs>
    using f = typename _list_wrap_if_c<!call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_list_wrap_if_not
  {
    using type = _list_wrap_if_not<Pred>;
  };

  template<class x, class C>
  struct mk_list_wrap_if_not<same_as<x, not_<C>>>
  : mk_list_wrap_if<same_as<x, C>>
  {};

  template<class C>
  struct mk_list_wrap_if_not<same<not_<C>>>
  : mk_list_wrap_if<same<C>>
  {};

  template<class C>
  struct mk_list_wrap_if_not<not_<C>>
  : mk_list_wrap_if<C>
  {};

  template<class Pred>
  struct mk_list_wrap_if_not<fork<Pred, not_<>>>
  : mk_list_wrap_if<Pred>
  {};
}
namespace jln::mp
{
  template<class Pred, class C = listify>
  using remove_if = transform<list_wrap_if_not<Pred>, join<C>>;

  template<class T, class C = listify>
  using remove = remove_if<same_as<T>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using remove_if = unpack<L, mp::remove_if<Pred, C>>;

    template<class L, class T, class C = mp::listify>
    using remove = unpack<L, mp::remove<T, C>>;
  }
}
namespace jln::mp
{
  template<class Pred, class C = listify>
  using copy_if = remove_if<fork<Pred, not_<>>, C>;

  template<class x, class C = listify>
  using copy = remove_if<same_as<x, not_<>>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using copy_if = unpack<L, mp::copy_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using copy = unpack<L, mp::copy<x, C>>;
  }
}
namespace jln::mp
{
  template<class C = identity>
  struct to_bool
  {
    template<class x>
    using f = call<C, number<bool(x::value)>>;
  };

  namespace emp
  {
    template<class x>
    using to_bool = number<bool(x::value)>;
  }
}
namespace jln::mp
{
  template<class Pred, class C = identity>
  using count_if = transform<Pred, add0<C>>;

  template<class x, class C = identity>
  using count = transform<same_as<x>, add0<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using count_if = unpack<L, mp::count_if<Pred, C>>;

    template<class L, class x, class C = mp::identity>
    using count = unpack<L, mp::count<x, C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<int, unsigned>
    struct _find;

    constexpr unsigned _first_find_select(unsigned n);
  }

  template<class Pred, class C = listify, class NC = C>
  struct find_if
  {
    template<class... xs>
    using f = typename detail::_find<-1,
      detail::_first_find_select(sizeof...(xs))
    >::template f<Pred, C, NC, xs...>;
  };

  template<class T, class C = listify, class NC = C>
  using find = find_if<same_as<T>, C, NC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using find_if = unpack<L, mp::find_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::listify, class NC = C>
    using find = unpack<L, mp::find_if<mp::same_as<T>, C, NC>>;
  }
}


namespace jln::mp
{
  namespace detail
  {
    template<unsigned>
    struct _drop;

    template<int_ i, unsigned n>
    using validate_index = number<(0 * std::size_t{int_(n) - i}) + i>;
  }

  template<class N, class C = listify>
  struct drop
  {
    template<class... xs>
    using f = typename detail::_drop<
      detail::n_8_or_less_16_64_256(
        detail::validate_index<N::value, sizeof...(xs)>::value
      )
    >::template f<N::value, C, xs...>;
  };

  template<int_ n, class C = listify>
  using drop_c = drop<number<n>, C>;

  template<class C>
  struct drop<number<0>, C>
  {
    template<class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<1>, C>
  {
    template<class, class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<2>, C>
  {
    template<class, class, class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<3>, C>
  {
    template<class, class, class, class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<4>, C>
  {
    template<class, class, class, class, class... xs>
    using f = call<C, xs...>;
  };

  template<class C>
  struct drop<number<5>, C>
  {
    template<class, class, class, class, class, class... xs>
    using f = call<C, xs...>;
  };

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using drop = unpack<L, mp::drop<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using drop_c = unpack<L, mp::drop<number<n>, C>>;
  }
}

namespace jln::mp::detail
{
#define JLN_MP_DROP_IMPL(n, _, mp_rxs, mp_rep) \
  template<>                                   \
  struct _drop<n>                              \
  {                                            \
    template<unsigned size, class C,           \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)   \
      class... xs>                             \
    using f = typename C::template f<xs...>;   \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL

#define JLN_MP_DROP_IMPL(n, mp_xs, mp_rxs, mp_rep) \
  JLN_MP_DROP_IMPL2(n, mp_xs, mp_rxs, mp_rep,      \
    n_8_or_less_16_64_256)

#define JLN_MP_DROP_IMPL2(n, _, mp_rxs, mp_rep, next_int) \
  template<>                                              \
  struct _drop<n>                                         \
  {                                                       \
    template<unsigned size, class C,                      \
      mp_rep(class JLN_MP_COMMA, JLN_MP_NIL)              \
      class... xs>                                        \
    using f = typename _drop<next_int (size-n)>           \
      ::template f<(size-n), C, xs...>;                   \
  };

  JLN_MP_GEN_XS_8_args(JLN_MP_DROP_IMPL2, JLN_MP_NIL)
  JLN_MP_GEN_XS_16_64_256(JLN_MP_DROP_IMPL)

#undef JLN_MP_DROP_IMPL2
#undef JLN_MP_DROP_IMPL
}
namespace jln::mp::detail
{
  constexpr unsigned _first_find_select(unsigned n)
  {
    return
      n == 0 ? 0
    : n < 64 ? 17
    : n < 256 ? 65
    : 257
    ;
  }

  template<int i, unsigned>
  struct _find
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename drop_c<i, C>::template f<xs...>;
  };

  template<>
  struct _find<-1, 0>
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename NC::template f<>;
  };

  template<bool... xs>
  constexpr int _index_of()
  {
    unsigned i = 0;
    (void)(... && (!xs && ++i));
    return i >= sizeof...(xs) ? -1 : int(i);
  }

#define JLN_MP_FIND_IMPL(nprev, mp_dup)                  \
  template<>                                             \
  struct _find<-1, nprev+16>                             \
  {                                                      \
    template<class Pred, class C, class NC,              \
      mp_dup(class, JLN_MP_COMMA),                       \
      class... xs>                                       \
    using f = typename _find<                            \
      _index_of<bool(Pred::template f<xs>::value)...>(), \
      0>                                                 \
    ::template f<Pred, C, NC, xs...>;                    \
  };

  JLN_MP_FIND_IMPL(0, JLN_MP_REPEAT_16)
  JLN_MP_FIND_IMPL(64, JLN_MP_REPEAT_64)
  JLN_MP_FIND_IMPL(256, JLN_MP_REPEAT_256)

#undef JLN_MP_FIND_IMPL

  template<>
  struct _find<-1, 17>
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename _find<
      _index_of<bool(Pred::template f<xs>::value)...>(),
      0>
    ::template f<Pred, C, NC, xs...>;
  };

  constexpr unsigned _find_select(unsigned n, unsigned r)
  {
    return
      n == 0 ? 0
    : (n < 64 ? 16
    : n < 256 ? 64
    : 256) + r
    ;
  }

#define JLN_MP_FIND_IMPL(nprev, n, mp_skip, mp_xs) \
  template<>                                       \
  struct _find<-1, nprev+n>                        \
  {                                                \
    template<class Pred, class C, class NC,        \
      mp_skip(class, JLN_MP_COMMA),                \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),      \
      class... xs>                                 \
    using f = typename _find<                      \
      _index_of<mp_xs(                             \
        bool JLN_MP_PAREN_OPEN Pred::template f<,  \
        >::value JLN_MP_PAREN_CLOSE, JLN_MP_COMMA  \
      )>(),                                        \
      _find_select(sizeof...(xs), n)               \
    >                                              \
    ::template f<                                  \
      Pred, C, NC,                                 \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), \
      xs...                                        \
    >;                                             \
  };

  JLN_MP_FIND_IMPL(64, 64, JLN_MP_REPEAT_64, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, 64, JLN_MP_REPEAT_256, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, 256, JLN_MP_REPEAT_256, JLN_MP_XS_256)

#undef JLN_MP_FIND_IMPL

#define JLN_MP_FIND_IMPL(n, mp_xs)                 \
  template<>                                       \
  struct _find<-1, n+1>                            \
  {                                                \
    template<class Pred, class C, class NC,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),      \
      class... xs>                                 \
    using f = typename _find<                      \
      _index_of<mp_xs(                             \
        bool JLN_MP_PAREN_OPEN Pred::template f<,  \
        >::value JLN_MP_PAREN_CLOSE, JLN_MP_COMMA  \
      )>(),                                        \
      _find_select(sizeof...(xs), n)>              \
    ::template f<                                  \
      Pred, C, NC,                                 \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), \
      xs...>;                                      \
  };

  JLN_MP_FIND_IMPL(64, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, JLN_MP_XS_256)

#undef JLN_MP_FIND_IMPL
}
namespace jln::mp
{
  namespace detail
  {
    template<template<class...> class, class>
    struct _flatten;

    template<class S>
    struct wrapper;
  }

  template<class S = cfe<list>, class C = listify>
  struct flatten;

  template<template<class...> class S, class C>
  struct flatten<cfe<S, identity>, C>
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>
      ::template f<C, typename detail::_flatten<S, seqs>::type...>
      ::type;
  };

  template<class S>
  using wrapper = typename detail::wrapper<S>::type;

  namespace emp
  {
    template<class L, class S = wrapper<L>, class C = mp::listify>
    using flatten = unpack<L, mp::flatten<S, C>>;
  }
}

namespace jln::mp::detail
{
  template<template<class...> class, class T>
  struct _flatten
  {
    using type = list<T>;
  };

  template<template<class...> class S, class... xs>
  struct _flatten<S, S<xs...>>
  : _join_select<sizeof...(xs)>
    ::template f<listify, typename _flatten<S, xs>::type...>
  {};

  template<template<class...> class S, class... xs>
  struct wrapper<S<xs...>>
  {
    using type = cfe<S>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _fold_right;
  }

  template<class F, class C = identity>
  struct fold_right
  {
    template<class state, class... xs>
    using f = typename C::template f<
      typename detail::_fold_right<
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))
      >::template f<F::template f, state, xs...>
    >;
  };

  namespace emp
  {
    template<class L, class state, class C = mp::identity>
    using fold_right = unpack<L,
      mp::push_front<state, mp::fold_right<C>>>;
  }
}


namespace jln::mp::detail
{
#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct _fold_right<n>                                    \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),              \
      class... xs>                                         \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      typename _fold_right<                                \
        detail::n_4_or_less_8_16_64_256(sizeof...(xs))     \
      >::template f<F, state, xs...>                       \
    mp_dup(>, JLN_MP_NIL);                                 \
  };

  JLN_MP_GEN_XS_4_8_16_64_256(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

#define JLN_MP_FOLD_RIGHT_SELECT(n, mp_xs, mp_rxs, mp_dup) \
  template<>                                               \
  struct _fold_right<n>                                    \
  {                                                        \
    template<template<class...> class F, class state,      \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA)>              \
    using f = mp_xs(F<, JLN_MP_COMMA, JLN_MP_NIL)          \
      state mp_dup(>, JLN_MP_NIL);                         \
  };

  JLN_MP_GEN_XS_1_TO_4(JLN_MP_FOLD_RIGHT_SELECT)

#undef JLN_MP_FOLD_RIGHT_SELECT

  template<>
  struct _fold_right<0>
  {
    template<template<class...> class, class state>
    using f = state;
  };
}
namespace jln::mp
{
  struct na;
  using is_na = same_as<na>;
  using violation = always<na>;

  namespace detail
  {
    template<class F, class... xs>
    typename F::template f<xs...>
    _try_invoke(F*, xs*...);

    na _try_invoke(...);

    template<class x>
    struct _try_invoke_dispatch;
  }

  template<class F, class TC = identity, class FC = violation>
  struct try_invoke;

  template<class F, class FC>
  using try_invoke_or = try_invoke<F, identity, FC>;

  template<class F, class TC, class FC>
  struct try_invoke
  {
    template<class... xs>
    using f = typename detail::_try_invoke_dispatch<
      decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class F, class TC, class FC, class... xs>
    using try_invoke = typename try_invoke<F, TC, FC>::template f<xs...>;
    
    template<class F, class FC, class... xs>
    using try_invoke_or = typename try_invoke<F, mp::identity, FC>::template f<xs...>;
  }
}


namespace jln::mp
{
  template<class F>
  struct try_invoke<F, always<true_>, always<false_>>
  {
    template<class... xs>
    using f = number<!std::is_same<na, decltype(detail::_try_invoke(
        static_cast<F*>(nullptr),
        static_cast<xs*>(nullptr)...
      ))>::value>;
  };
}

namespace jln::mp::detail
{
  template<class x>
  struct _try_invoke_dispatch
  {
    template<class TC, class FC, class...>
    using f = typename TC::template f<x>;
  };

  template<>
  struct _try_invoke_dispatch<na>
  {
    template<class TC, class FC, class... xs>
    using f = typename FC::template f<xs...>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct _group;
  }

  template<class Cmp, class C = listify>
  struct group_if
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using group = group_if<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using group_if = unpack<L, mp::group_if<Cmp, C>>;

    template<class L, class C = mp::listify>
    using group = unpack<L, mp::group<C>>;
  }
}


namespace jln::mp
{
  namespace detail
  {
    template <bool>
    struct _split;

    inline constexpr int_ split_keep = 0;
    inline constexpr int_ split_after = 1;
    inline constexpr int_ split_before = 2;
    inline constexpr int_ split_skip = 3;
    // inline constexpr int_ split_na = 4;
  }

  template<class Pred = identity, class C = listify>
  struct split_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_skip, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split = split_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred = mp::identity, class C = mp::listify>
    using split_if = unpack<L, mp::split_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split = unpack<L, mp::split<x, C>>;
  }
}

namespace jln::mp::detail
{
  template <class x, class state>
  struct split_state;

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_keep>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_after>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<x>, list<xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_before>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<x, xs...>, Ls...>;
  };

  template<class x, class... Ls, class... xs>
  struct split_state<list<number<split_skip>, x>, list<list<xs...>, Ls...>>
  {
    using type = list<list<>, list<xs...>, Ls...>;
  };

  template<>
  struct _split<true>
  {
    template<int_ policy, class C, class Pred, class... xs>
    using f = call<
      fold_right<cfl<split_state>, optimize_useless_unpack_t<unpack<C>>>,
      list<list<>>,
      list<number<bool{Pred::template f<xs>::value}
        ? policy : split_keep>, xs>...
    >;
  };

  template<>
  struct _split<false>
  {
    template<int_, class C, class>
    using f = typename C::template f<>;
  };
}
namespace jln::mp
{
  template<class N, class C = listify>
  struct take
  {
    template<class... xs>
    using f = call<
      rotate<N, drop<number<sizeof...(xs) - N::value>, C>>,
      xs...>;
  };

  template<int_ n, class C = listify>
  using take_c = take<number<n>, C>;

  namespace emp
  {
    template<class L, class N, class C = mp::listify>
    using take = unpack<L, mp::take<N, C>>;

    template<class L, int_ n, class C = mp::listify>
    using take_c = unpack<L, mp::take<number<n>, C>>;
  }
}

namespace jln::mp
{
  template<class F>
  struct fork_front
  {
    template<class... xs>
    using f = typename call<F, xs...>::template f<xs...>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template <class, class...>
    struct _partial;
  }

  template <class... Fs>
  struct partial
  : rotate<number<-1>, cfe<detail::_partial>>
  ::template f<Fs...>
  {};

  template <class C>
  struct partial<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial<F, C>
  {
    template <class x, class... xs>
    using f = call<C, call<F, x>, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial<F0, F1, C>
  {
    template <class x0, class x1, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, xs...>;
  };

  template <class F0, class F1, class F2, class C>
  struct partial<F0, F1, F2, C>
  {
    template <class x0, class x1, class x2, class... xs>
    using f = call<C, call<F0, x0>, call<F1, x1>, call<F2, x2>, xs...>;
  };
}

namespace jln::mp
{
  namespace detail
  {
    template <class C, class... Fs>
    struct _each;
  }

  template <class... Fs>
  struct each
  : rotate<number<-1>, cfe<detail::_each>>
  ::template f<Fs...>
  {};

  template <class C>
  struct each<C> : detail::_each<C>
  {};

  template <class F, class C>
  struct each<F, C> : detail::_each<C, F>
  {};

  template <class F0, class F1, class C>
  struct each<F0, F1, C> : detail::_each<C, F0, F1>
  {};

  template <class F0, class F1, class F2, class C>
  struct each<F0, F1, F2, C> : detail::_each<C, F0, F1, F2>
  {};
}

namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _each
  {
    template <class... xs>
    using f = call<C, call<Fs, xs>...>;
  };
} // namespace jln::mp
namespace jln::mp::detail
{
  template <class C, class... Fs>
  struct _partial
  {
    template<class... xs>
    using f = typename _join_select<2>::f<
      cfe<_each>,
      list<C, Fs...>,
      emp::make_int_sequence_c<sizeof...(xs) - sizeof...(Fs), transform<always<identity>>>
    >::type::template f<xs...>;
  };
} // namespace jln::mp
namespace jln::mp::detail
{
  template<class x, class C>
  using _group_insert_x = partial<unpack<push_front<x>>, C>;

  template<class...>
  struct _group_impl;

  template<class C, class Cmp, class x, class... xs, class... ys>
  struct _group_impl<C, Cmp, x, list<ys...>, xs...>
  {
    using type = call<
      fold_right<cfl<split_state>, unpack<_group_insert_x<x, C>>>,
      list<list<>>,
      list<number<Cmp::template f<ys, xs>::value
        ? split_keep : split_before>, xs>...
    >;
  };

  template<class... ys>
  struct _smp_group_impl
  {
    template<class C, class cmp, class x, class... xs>
    using f = call<
        fold_right<cfl<split_state>, unpack<_group_insert_x<x, C>>>,
        list<list<>>,
        list<number<bool(cmp::template f<ys, xs>::value)
          ? split_keep : split_before>, xs>...
      >;
  };

  template<class C, class Cmp, class TC, class FC, class x, class... xs, class... ys>
  struct _group_impl<C, try_invoke<Cmp, TC, FC>, x, list<ys...>, xs...>
  {
    using type = typename try_invoke<_smp_group_impl<ys...>>
      ::template f<C, try_invoke<Cmp, TC, FC>, x, xs...>;
  };

  template<>
  struct _group<true>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename _group_impl<
      C, Cmp, x,
      call<take_c<sizeof...(xs)>, x, xs...>,
      xs...
    >::type;
  };

  template<>
  struct _group<false>
  {
    template<class C, class>
    using f = typename C::template f<>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<bool>
    struct _group_n;
  }

  template<class n, class C = listify>
  struct group_n
  {
    template<class... xs>
    using f = typename detail::_group_n<sizeof...(xs) != 0 && (n::value > 0)>
      ::template f<C, n::value, xs...>;
  };

  template<int_ n, class C = listify>
  using group_n_c = group_n<number<n>, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using group_n = unpack<L, mp::group_n<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using group_n_c = unpack<L, mp::group_n_c<n, C>>;
  }
}


namespace jln::mp
{
  template<class C = listify>
  using pop_front = drop<number<1>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_front = drop<L, mp::number<1>, C>;
  }
}
namespace jln::mp::detail
{
  template<int_... i>
  struct _group_n_impl
  {
    template<class C, unsigned long long n, class... xs>
    using f = call<
      fold_right<cfl<split_state>, unpack<pop_front<C>>>,
      list<list<>>,
      list<number<(i % n ? split_keep : split_before)>, xs>...
    >;
  };

  template<>
  struct _group_n<true>
  {
    template<class C, unsigned long long n, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), cfe_c<_group_n_impl>
    >::template f<C, n, xs...>;
  };

  template<>
  struct _group_n<false>
  {
    template<class C, unsigned long long, class...>
    using f = typename C::template f<>;
  };
}
namespace jln::mp
{
  template<class F, class C = identity>
  struct index_for
  {
    template<class... xs>
    using f = typename C::template f<number<int_(sizeof...(xs)) - call<F, xs...>::value>>;
  };

  template<class F>
  struct index_for<F, identity>
  {
    template<class... xs>
    using f = number<int_(sizeof...(xs)) - call<F, xs...>::value>;
  };

  template<class Pred, class C = identity, class NC = always<na>>
  struct index_if
  {
    template<class... xs>
    using f = typename find_if<Pred, size<push_front<number<sizeof...(xs)>, sub<C>>>, NC>
      ::template f<xs...>;
  };

  template<class T, class C = listify, class NC = always<na>>
  using index_of = index_if<same_as<T>, C, NC>;

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using index_for = unpack<L, mp::index_for<F, C>>;

    template<class L, class Pred, class C = mp::identity, class NC = mp::always<na>>
    using index_if = unpack<L, mp::index_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::identity, class NC = mp::always<na>>
    using index_of = unpack<L, mp::index_of<T, C, NC>>;
  }
}
namespace jln::mp
{
  template<class C = listify>
  using indices = size<make_int_sequence<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using indices = unpack<L, mp::indices<C>>;
  }
} // namespace jln::mp
namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _intersperse;
  }

  template<class x, class C = listify>
  struct intersperse
  {
    template<class... xs>
    using f = typename detail::_intersperse<sizeof...(xs) ? 1 : 0>
      ::template f<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using intersperse = unpack<L, mp::intersperse<x, C>>;
  }
}


namespace jln::mp
{
  namespace detail
  {
    struct _drop_back;

    template<class C = listify>
    struct _zip;
  }

  template<class C = listify>
  using zip = detail::_zip<detail::optimize_useless_transform_unpack_t<C>>;

  template<class F = listify, class C = listify>
  using zip_with = zip<transform<unpack<F>, C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using zip = unpack<L, mp::zip<C>>;

    template<class L, class F = mp::listify, class C = mp::listify>
    using zip_with = unpack<L, mp::zip_with<F, C>>;
  }
}

namespace jln::mp::detail
{
  template<class...>
  struct _zip_impl;

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)         \
  template<class C, mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
  struct _zip_impl<C, mp_xs(list<, ...>, JLN_MP_COMMA)>         \
  {                                                             \
    using type = typename C::template f<list<                   \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)               \
    >...>;                                                      \
  };                                                            \
                                                                \
  template<class F, class C,                                    \
    mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>                  \
  struct _zip_impl<                                             \
    transform<unpack<F>, C>, mp_xs(list<, ...>, JLN_MP_COMMA)>  \
  {                                                             \
    using type = typename C::template f<typename F::template f< \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)               \
    >...>;                                                      \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)
  JLN_MP_TRANSPOSE_IMPL(8, JLN_MP_XS_8, _, _)

#undef JLN_MP_TRANSPOSE_IMPL

  template<int>
  struct _zip_dispatch;

  template<class C>
  struct _zip
  {
    template<class... seqs>
    using f = typename _zip_dispatch<
      sizeof...(seqs) ? (sizeof...(seqs) > 8 ? 2 : 1) : 0
    >::template f<C, seqs...>;
  };

  template<>
  struct _zip_dispatch<0>
  {
    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _zip_dispatch<1>
  {
    template<class C, class... seqs>
    using f = typename _zip_impl<C, seqs...>::type;
  };

  template<int>
  struct _recursive_zip
  {
    template<int n, class C,
      class _0, class _1, class _2, class _3, class _4,
      class _5, class _6, class _7, class... seqs>
    using f = typename _recursive_zip<(n >= 8 ? 8 : n)>
      ::template f<
        n-8, C, seqs..., typename _zip_impl<listify,
          _0, _1, _2, _3, _4, _5, _6, _7>::type
      >;
  };

  template<>
  struct _recursive_zip<0>
  {
    template<int, class C, class... seqs>
    using f = typename zip<transform<unpack<join<>>, C>>
      ::template f<seqs...>;
  };

#define JLN_MP_TRANSPOSE_IMPL(n, mp_xs, mp_rxs, mp_rep)      \
  template<>                                                 \
  struct _recursive_zip<n>                                   \
  {                                                          \
    template<int, class C                                    \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL),     \
      class... seqs>                                         \
    using f = typename zip<transform<unpack<join<>>, C>>     \
      ::template f<seqs..., typename _zip_impl<listify,      \
        mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>::type>; \
  };

  JLN_MP_GEN_XS_1_TO_8(JLN_MP_TRANSPOSE_IMPL)

#undef JLN_MP_TRANSPOSE_IMPL

  template<>
  struct _zip_dispatch<2>
  {
    template<class C, class... seqs>
    using f = typename _recursive_zip<
      (sizeof...(seqs) >= 8 ? 8 : sizeof...(seqs))
    >::template f<sizeof...(seqs)-8, C, seqs...>;
  };
}
namespace jln::mp::detail
{
  template<>
  struct _intersperse<0>
  {
    template<class C, class x>
    using f = typename C::template f<>;
  };

  template<>
  struct _intersperse<1>
  {
    template<class C, class x, class... xs>
    using f = typename _zip_impl<
      join<pop_front<C>>,
      emp::make_int_sequence_c<sizeof...(xs), transform<always<x>>>,
      list<xs...>
    >::type;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<int_ start, int_ stride, bool inc>
    struct _iota_v_c;
  }

  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::_iota_v_c<start::value, stride::value, (count::value >= 0)>
      ::template f<C, count::value>;
  };

  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::_iota_v_c<start, stride, (count >= 0)>
      ::template f<C, count>;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = iota_v_c<start::value, count::value, stride::value, C>;

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
    using iota_c = iota_v_c<start, count, stride, mp::numbers<C>>;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = iota_v_c<start::value, count::value, stride::value, mp::numbers<C>>;
  }
}

namespace jln::mp::detail
{
  template<int_ start, int_ stride, class C>
  struct _iota
  {
    template<int_... ns>
    using f = typename C::template f<(start + ns * stride)...>;
  };

  template<int_ start, int_ stride>
  struct _iota<start, stride, numbers<>>
  {
    template<int_... ns>
    using f = list<number<(start + ns * stride)>...>;
  };

  template<>
  struct _iota_v_c<0, 1, true>
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<count, C>;
  };

  template<int_ start, int_ stride, bool>
  struct _iota_v_c
  {
    template<class C, int_ count>
    using f = emp::make_int_sequence_v_c<
      (count < 0 ? -count : count),
      detail::_iota<start, (count < 0 ? -stride : stride), C>>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<unsigned>
    struct _is_sorted;
  }

  template<class Cmp = less<>, class C = identity>
  struct is_sorted
  {
    template<class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
        ::template f<Cmp, xs...>>;
  };

  template<class Cmp>
  struct is_sorted<Cmp, identity>
  {
    template<class... xs>
    using f = typename detail::_is_sorted<detail::min(sizeof...(xs), 3)>
      ::template f<Cmp, xs...>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using is_sorted = unpack<L, mp::is_sorted<Cmp, C>>;
  }
}


namespace jln::mp::detail
{
  template<>
  struct _is_sorted<0>
  {
    template<class Cmp>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<1>
  {
    template<class Cmp, class x>
    using f = number<1>;
  };

  template<>
  struct _is_sorted<2>
  {
    template<class Cmp, class x, class y>
    using f = number<!Cmp::template f<y, x>::value>;
  };

  template<>
  struct _is_sorted<3>
  {
    template<class Cmp, class x, class y, class... xs>
    using f = typename zip_with<Cmp, or_<not_<>>>::template f<
      list<y, xs...>,
      rotate_c<-1, pop_front<>>::f<x, y, xs...>
    >;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }

  template<class C = listify>
  using unique = typename detail::mk_unique<cfe<std::is_same>, C>::type;

  template<class Cmp = cfe<std::is_same>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = unpack<L, unique<C>>;

    template<class L, class Cmp = cfe<std::is_same>, class C = mp::listify>
    using unique_if = unpack<L, unique_if<Cmp, C>>;
  }
}


namespace jln::mp::detail
{
  template<class x>
  struct _inherit_impl {};
  template<std::size_t i, class x>
  struct inherit_impl : _inherit_impl<x> {};

  template<class, class...>
  struct inherit;

  template<std::size_t... ints, class... xs>
  struct inherit<std::integer_sequence<std::size_t, ints...>, xs...>
    : inherit_impl<ints, xs>...
  {};

  template<class L, class x, class = void>
  struct _set_push_back
  {
    using type = L;
  };

  template<class... xs, class x>
  struct _set_push_back<list<xs...>, x,
    std::enable_if_t<sizeof(inherit<std::make_index_sequence<sizeof...(xs)+1>, xs..., x>) == 1>>
  {
    using type = list<xs..., x>;
  };

  template<class> using to_false = std::false_type;

  struct _set_cmp_push_back_impl
  {
    template<class Cmp, class x, class... xs>
    using f = typename conditional_c<std::is_same<
      list<std::bool_constant<Cmp::template f<xs, x>::value>...>,
      list<to_false<xs>...>
    >::value>::template f<list<xs..., x>, list<xs...>>;
  };

  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class L, class x>
    using f = typename unpack<_set_cmp_push_back_impl>::template f<L, Cmp, x>;
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold_left<
      _set_cmp_push_back<Cmp>,
      unpack<C>
    >>;
  };

  template<class C>
  struct mk_unique<cfe<std::is_same>, C>
  {
    using type = push_front<list<>, fold_left<
      cfl<_set_push_back>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<cfl<std::is_same>, C>
  : mk_unique<cfe<std::is_same>, C>
  {};

  template<class C>
  struct mk_unique<same<>, C>
  : mk_unique<cfe<std::is_same>, C>
  {};
}
namespace jln::mp
{
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_is_unique;
  }

  template<class C = identity>
  using is_unique = typename detail::mk_is_unique<cfe<std::is_same>, C>::type;

  template<class Cmp = cfe<std::is_same>, class C = identity>
  using is_unique_if = typename detail::mk_is_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_unique = unpack<L, is_unique<C>>;

    template<class L, class Cmp = cfe<std::is_same>, class C = mp::identity>
    using is_unique_if = unpack<L, is_unique_if<Cmp, C>>;
  }
}


namespace jln::mp::detail
{
  template<class C>
  struct _is_unique
  {
    template<class... xs>
    using f = typename dcall<(sizeof...(xs) < 100000)>::template f<
      C, mp::number<sizeof(inherit<std::make_index_sequence<sizeof...(xs)>, xs...>) == 1>>;
  };

  template<class Cmp, class C>
  struct _is_unique2
  {
    template<class... xs>
    using f = typename dcall<(sizeof...(xs) < 100000)>::template f<C, mp::number<std::is_same<
      typename unique_if<Cmp, C>::template f<xs...>,
      list<xs...>
    >::value>>;
  };

  template<class Cmp, class C>
  struct mk_is_unique
  {
    using type = fork<unique_if<Cmp>, listify, cfl<std::is_same, to_bool<C>>>;
  };

  template<class C>
  struct mk_is_unique<cfe<std::is_same>, C>
  {
    using type = _is_unique<C>;
  };

  template<class C>
  struct mk_is_unique<cfl<std::is_same>, C>
  : mk_is_unique<cfe<std::is_same>, C>
  {};

  template<class C>
  struct mk_is_unique<same<>, C>
  : mk_is_unique<cfe<std::is_same>, C>
  {};
}
namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _lower_bound;

    constexpr int _lower_bound_select(unsigned n);

    template<class>
    struct optimize_cmp;
  }

  template<class x, class Cmp = less<>, class C = listify, class NC = C>
  struct lower_bound
  {
    template<class... xs>
    using f = typename detail::_lower_bound<
      detail::_lower_bound_select(sizeof...(xs))
    >::template f<
      sizeof...(xs),
      push_back<x, typename detail::optimize_cmp<Cmp>::type>,
      C, NC, xs...>;
  };

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using lower_bound_c = lower_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using lower_bound_of = lower_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using lower_bound_of_c = lower_bound<number<x>, less<>, C, NC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using lower_bound = unpack<L, mp::lower_bound<x, Cmp, C, NC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using lower_bound_c = unpack<L, mp::lower_bound<mp::number<x>, Cmp, C, NC>>;

    template<class L, class x, class C = mp::listify, class NC = C>
    using lower_bound_of = unpack<L, mp::lower_bound<x, mp::less<>, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using lower_bound_of_c = unpack<L, mp::lower_bound<mp::number<x>, mp::less<>, C, NC>>;
  }
}


namespace jln::mp
{
  template<class C = identity>
  struct front
  {
    template<class x, class... xs>
    using f = typename C::template f<x>;
  };

  template<>
  struct front<identity>
  {
    template<class x, class...>
    using f = x;
  };

  namespace emp
  {
    template<class L, class C = mp::identity>
    using front = unpack<L, front<C>>;
  }
}
namespace jln::mp
{
  template<class C = listify>
  struct flip
  {
    template<class x0, class x1, class... xs>
    using f = call<C, x1, x0, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using flip = unpack<L, mp::flip<C>>;
  }
}
namespace jln::mp::detail
{
  template<class Cmp>
  struct optimize_cmp
  {
    using type = Cmp;
  };

  template<class Cmp>
  struct optimize_cmp<flip<fork<less<Cmp>, not_<>>>>
  {
    using type = flip<less<not_<Cmp>>>;
  };

  template<class Cmp, class C>
  struct optimize_cmp<flip<fork<flip<Cmp>, C>>>
  : optimize_cmp<fork<Cmp, C>>
  {};

  template<class C>
  struct optimize_cmp<fork<less<>, C>>
  {
    using type = less<C>;
  };

  template<int>
  struct _smp_lower_bound;

  template<class Bool, class = void>
  struct _smp_conditional
  {
    template<class C, class NC>
    using f = violation;
  };

  template<class Bool>
  struct _smp_conditional<Bool, decltype(void(bool(Bool::value)))>
  {
    template<class C, class NC>
    using f = typename conditional_c<bool(Bool::value)>::template f<C, NC>;
  };

  struct _lower_bound_violation2
  {
    template<unsigned, class...>
    using f = na;
  };

  template<class Bool, class = void>
  struct _smp_conditional2
  {
    template<class C, class NC>
    using f = _lower_bound_violation2;
  };

  template<class Bool>
  struct _smp_conditional2<Bool, decltype(void(bool(Bool::value)))>
  {
    template<class C, class NC>
    using f = typename conditional_c<bool(Bool::value)>::template f<C, NC>;
  };

  constexpr int _lower_bound_select(unsigned n)
  {
    return
      n < 2 ? -n
    : n < 4 ? 2
    : n < 8 ? 4
    : n < 16 ? 8
    : n < 32 ? 16
    : n < 64 ? 32
    : n < 128 ? 64
    : n < 256 ? 128
    : 256
    ;
  }

#define JLN_MP_LOWER_BOUND_IMPL(prefix, Cond)              \
  template<>                                               \
  struct prefix##lower_bound<0>                            \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class... xs>                                         \
    using f = typename NC::template f<>;                   \
  };                                                       \
                                                           \
  /* original size == 1 */                                 \
  template<>                                               \
  struct prefix##lower_bound<-1>                           \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class x>                                             \
    using f = typename Cond(x)                             \
      ::template f<_cartesian<NC, 0> /* for NC::f<> */, C> \
      ::template f<x>;                                     \
  };                                                       \
                                                           \
  template<>                                               \
  struct prefix##lower_bound<1>                            \
  {                                                        \
    template<unsigned n, class Pred, class C, class NC,    \
      class x, class... xs>                                \
    using f = typename Cond(x)                             \
      ::template f<pop_front<C>, C>                        \
      ::template f<x, xs...>;                              \
  };

#define JLN_MP_LOWER_BOUND_PRED_CALL(x) \
  conditional_c<bool(Pred::template f<x>::value)>

#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional<typename Pred::template f<x>>

  JLN_MP_LOWER_BOUND_IMPL(_, JLN_MP_LOWER_BOUND_PRED_CALL)
  JLN_MP_LOWER_BOUND_IMPL(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL)

#undef JLN_MP_LOWER_BOUND_IMPL

  template<unsigned> struct _lower_bound_drop;
  template<unsigned> struct _smp_lower_bound_drop;

#define JLN_MP_LOWER_BOUND_IMPL2(prefix, Cond, n, mp_xs) \
  template<>                                             \
  struct prefix##lower_bound_drop<n>                     \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename detail::prefix##lower_bound<      \
      _lower_bound_select(count-n)                       \
    >::template f<count-n, Pred, C, NC, xs...>;          \
  };                                                     \
                                                         \
  template<>                                             \
  struct prefix##lower_bound<n>                          \
  {                                                      \
    template<int count, class Pred, class C, class NC,   \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),            \
      class... xs>                                       \
    using f = typename Cond(_##n)::template f<           \
      prefix##lower_bound_drop<n>,                       \
      prefix##lower_bound<n/2>                           \
    >::template f<count, Pred, C, NC,                    \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),       \
      xs...                                              \
    >;                                                   \
  };

#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
#define JLN_MP_LOWER_BOUND_SMP_PRED_CALL(x) \
  _smp_conditional2<typename Pred::template f<x>>

#define JLN_MP_LOWER_BOUND_IMPL(n, mp_xs, mp_rxs, mp_rep)             \
  JLN_MP_LOWER_BOUND_IMPL2(_, JLN_MP_LOWER_BOUND_PRED_CALL, n, mp_xs) \
  JLN_MP_LOWER_BOUND_IMPL2(_smp_, JLN_MP_LOWER_BOUND_SMP_PRED_CALL, n, mp_xs)

  JLN_MP_GEN_XS_2_4_8_16_32_64_128_256(JLN_MP_LOWER_BOUND_IMPL)

#undef JLN_MP_LOWER_BOUND_IMPL
#undef JLN_MP_LOWER_BOUND_PRED_CALL
#undef JLN_MP_LOWER_BOUND_SMP_PRED_CALL
}
namespace jln::mp
{
  namespace detail
  {
    struct _drop_back
    {
      template<int_ min, class n>
      using impl = typename conditional_c<min != n::value>
        ::template f<unpack<take_c<min>>, identity>;

      template<class C, class... ns>
      using f = _each<C, impl<std::min({int_(~0u), ns::value...}), ns>...>;
    };
  }

  template<class C = listify>
  struct matrix_shortest
  {
    template<class... seqs>
    using f = typename detail::_drop_back::f<C, unpack<size<>>::f<seqs>...>
      ::template f<seqs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using matrix_shortest = unpack<L, mp::matrix_shortest<C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class seq>
    struct _as_list
    {};
  }

  template<class C = listify>
  struct as_list
  {
    template<class seq>
    using f = typename unpack<C>::template f<typename detail::_as_list<seq>::type>;
  };

  template<>
  struct as_list<listify>
  {
    template<class seq>
    using f = typename detail::_as_list<seq>::type;
  };

  namespace emp
  {
    template<class seq, class C = mp::listify>
    using as_list = typename as_list<C>::template f<seq>;
  }
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
namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _unpack_merge;

    template<bool, bool>
    struct _dispatch_merge;
  }

  template<class Cmp = less<>, class C = listify>
  struct merge
  {
    template<class seq1, class seq2>
    using f = call<unpack<C>, typename detail::_dispatch_merge<std::is_same<seq1, list<>>::value, std::is_same<seq2, list<>>::value>
      ::template f<seq1, seq2>::template f<Cmp>::type>;
  };

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using merge = unpack<L, mp::merge<Cmp, C>>;
  }
}


namespace jln::mp
{
  template<class L, class C = listify>
  using prepend = push_front<L, unpack<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using prepend = unpack<L, listify, xs...>;
  }
}
#if __cplusplus > 201703L
namespace jln::mp::detail
{
  using std::type_identity;
}
#else
namespace jln::mp::detail
{
  template<class T>
  struct type_identity
  {
    using type = T;
  };
}
#endif
namespace jln::mp
{
  template<class Cmp>
  struct merge<Cmp, listify>
  {
    template<class seq1, class seq2>
    using f = typename detail::_dispatch_merge<std::is_same<seq1, list<>>::value, std::is_same<seq2, list<>>::value>
      ::template f<seq1, seq2>::template f<Cmp>::type;
  };
}

namespace jln::mp::detail
{
  template<class, class, class, class>
  struct _merge_impl
  {};

  template<class x, class y, class z = list<>, class = true_>
  struct _merge;

  template<bool, bool>
  struct _dispatch_merge
  {
    template<class x, class y>
    using f = _merge<x, y>;
  };

  template<>
  struct _dispatch_merge<true, true>
  {
    template<class x, class y>
    using f = always<type_identity<list<>>>;
  };

  template<template<class...> class Tpl, class... xs>
  struct _unpack_merge<Tpl<xs...>>
  {
    template<class>
    struct right
    {};

    template<template<class...> class Tpl2, class... ys>
    struct right<Tpl2<ys...>>
    {
      template<class cmp>
      using f = typename _merge<list<xs...>, list<ys...>>::template f<cmp>;
    };
  };

  template<template<class...> class Tpl>
  struct _unpack_merge<Tpl<>>
  {
    template<class L>
    struct right
    {
      template<class cmp>
      using f = unpack<listify>;
    };
  };

  constexpr int _fast_merge_impl_select(bool b, int xn, int yn)
  {
    return b ? (yn >= 4) : (xn >= 4) + 2;
  }

  template<int>
  struct _fast_merge_impl;

  template<>
  struct _fast_merge_impl<0>
  {
    template<class, class, class, class>
    struct f
    {};

    template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
    struct f<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
    : _merge_impl<list<xh, xt...>, list<yt...>, list<zs..., yh>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<1>
  {
    template<class, class, class, class, class = true_>
    struct f
    {};

    template<
      class xh, class... xt,
      class yh0, class yh1, class yh2, class yh3, class yh4, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh, xt...>,
      list<yh0, yh1, yh2, yh3, yh4, yt...>,
      list<zs...>, cmp,
      number<bool(call<cmp, yh4, xh>::value)>>
    : _merge_impl<list<xh, xt...>, list<yt...>, list<zs..., yh0, yh1, yh2, yh3, yh4>, cmp>
    {};

    template<
      class xh, class... xt,
      class yh0, class yh1, class yh2, class yh3, class yh4, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh, xt...>,
      list<yh0, yh1, yh2, yh3, yh4, yt...>,
      list<zs...>, cmp,
      number<!bool(call<cmp, yh4, xh>::value)>>
    : _merge_impl<list<xh, xt...>, list<yh1, yh2, yh3, yh4, yt...>, list<zs..., yh0>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<2>
  {
    template<class, class, class, class>
    struct f
    {};

    template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
    struct f<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
    : _merge_impl<list<xt...>, list<yh, yt...>, list<zs..., xh>, cmp>
    {};
  };

  template<>
  struct _fast_merge_impl<3>
  {
    template<class, class, class, class, class = true_>
    struct f
    {};

    template<
      class xh0, class xh1, class xh2, class xh3, class xh4, class... xt,
      class yh, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh0, xh1, xh2, xh3, xh4, xt...>,
      list<yh, yt...>,
      list<zs...>, cmp,
      number<!bool(call<cmp, yh, xh4>::value)>>
    : _merge_impl<list<xt...>, list<yh, yt...>, list<zs..., xh0, xh1, xh2, xh3, xh4>, cmp>
    {};

    template<
      class xh0, class xh1, class xh2, class xh3, class xh4, class... xt,
      class yh, class... yt,
      class... zs, class cmp>
    struct f<
      list<xh0, xh1, xh2, xh3, xh4, xt...>,
      list<yh, yt...>,
      list<zs...>, cmp,
      number<bool(call<cmp, yh, xh4>::value)>>
    : _merge_impl<list<xh1, xh2, xh3, xh4, xt...>, list<yh, yt...>, list<zs..., xh0>, cmp>
    {};
  };

  template<class xh, class... xt, class yh, class... yt, class... zs, class cmp>
  struct _merge_impl<list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
  : _fast_merge_impl<_fast_merge_impl_select(
    bool(call<cmp, yh, xh>::value), sizeof...(xt), sizeof...(yt)
  )>::template f<
    list<xh, xt...>, list<yh, yt...>, list<zs...>, cmp>
  {};

  template<class... xs, class... zs, class cmp>
  struct _merge_impl<list<xs...>, list<>, list<zs...>, cmp>
  {
    template<class x, class y>
    using part = typename _merge<emp::prepend<x, xs...>, y, list<zs...>>::template f<cmp>;

    using type = list<zs..., xs...>;
  };

  template<class... ys, class... zs, class cmp>
  struct _merge_impl<list<>, list<ys...>, list<zs...>, cmp>
  {
    template<class x, class y>
    using part = typename _merge<x, emp::prepend<y, ys...>, list<zs...>>::template f<cmp>;

    using type = list<zs..., ys...>;
  };

  template<class... xs, class... ys, class z>
  struct _merge<list<xs...>, list<ys...>, z, number<
    // x.size + y.size >= 100, unless empty list
    (unsigned{sizeof...(xs)-1LL} + unsigned{sizeof...(ys)-1LL} >= 98u)>>
  {
    using xm = number<(sizeof...(xs) + 1) / 2>;
    using ym = number<(sizeof...(ys) + 1) / 2>;

    using xl = call<take<xm>, xs...>;
    using yl = call<take<ym>, ys...>;

    using xr = call<drop<xm>, xs...>;
    using yr = call<drop<ym>, ys...>;

    using l = _merge<xl, yl, z>;

    template<class cmp>
    using f = typename l::template f<cmp>::template part<xr, yr>;
  };

  template<class x, class y, class z, class>
  struct _merge
  {
    template<class cmp>
    using f = _merge_impl<x, y, z, cmp>;
  };

  // could be deleted
  template<class x, class z>
  struct _merge<x, list<>, z>
  {
    template<class cmp>
    using f = _merge_impl<x, list<>, z, cmp>;
  };

  // could be deleted
  template<class y, class z>
  struct _merge<list<>, y, z>
  {
    template<class cmp>
    using f = _merge_impl<list<>, y, z, cmp>;
  };
}
namespace jln::mp
{
  template<class Pred, class C = identity>
  using none_of = any_of<Pred, not_<C>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using none_of = unpack<L, mp::none_of<Pred, C>>;
  }
} // namespace jln::mp
namespace jln::mp
{
  template<class Pred, class C = listify>
  using partition = fork<remove_if<Pred>, copy_if<Pred>, C>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using partition = unpack<L, mp::partition<C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _permutations;

    constexpr int _permutations_select(int n)
    {
      // -1 with big list result (5040 elements)
      return n > 7 ? -1 : n;
      // -1 with big list result (40320 elements)
      // return n > 8 ? -1 : n;
    }
  }

  template<class C = listify>
  struct permutations
  {
    template<class... xs>
    using f = typename detail::_permutations<detail::_permutations_select(sizeof...(xs))>
      ::template f<C, xs...>;
  };

  namespace emp
  {
    template<class L, class C = listify>
    using permutations = unpack<L, mp::permutations<C>>;
  }
}


namespace jln::mp::detail
{
  template<>
  struct _permutations<-1>
  {};

  template<>
  struct _permutations<0>
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };

  template<>
  struct _permutations<1>
  {
    template<class C, class x>
    using f = typename C::template f<list<x>>;
  };

  template<>
  struct _permutations<2>
  {
    template<class C, class x0, class x1>
    using f = typename C::template f<
      list<x0, x1>, list<x1, x0>
    >;
  };

  template<>
  struct _permutations<3>
  {
    template<class C, class x0, class x1, class x2>
    using f = typename C::template f<
      list<x0, x1, x2>, list<x0, x2, x1>,
      list<x1, x0, x2>, list<x1, x2, x0>,
      list<x2, x0, x1>, list<x2, x1, x0>
    >;
  };

  template<>
  struct _permutations<4>
  {
    template<class C, class x0, class x1, class x2, class x3>
    using f = typename C::template f<
      list<x0, x1, x2, x3>, list<x0, x1, x3, x2>,
      list<x0, x2, x1, x3>, list<x0, x2, x3, x1>,
      list<x0, x3, x1, x2>, list<x0, x3, x2, x1>,

      list<x1, x0, x2, x3>, list<x1, x0, x3, x2>,
      list<x1, x2, x0, x3>, list<x1, x2, x3, x0>,
      list<x1, x3, x0, x2>, list<x1, x3, x2, x0>,

      list<x2, x0, x1, x3>, list<x2, x0, x3, x1>,
      list<x2, x1, x0, x3>, list<x2, x1, x3, x0>,
      list<x2, x3, x0, x1>, list<x2, x3, x1, x0>,

      list<x3, x0, x1, x2>, list<x3, x0, x2, x1>,
      list<x3, x1, x0, x2>, list<x3, x1, x2, x0>,
      list<x3, x2, x0, x1>, list<x3, x2, x1, x0>
    >;
  };

  struct _insert_permutations4
  {
    template<class x, class x0, class x1, class x2, class x3>
    using f = list<
      list<x, x0, x1, x2, x3>, list<x, x0, x1, x3, x2>,
      list<x, x0, x2, x1, x3>, list<x, x0, x2, x3, x1>,
      list<x, x0, x3, x1, x2>, list<x, x0, x3, x2, x1>,

      list<x, x1, x0, x2, x3>, list<x, x1, x0, x3, x2>,
      list<x, x1, x2, x0, x3>, list<x, x1, x2, x3, x0>,
      list<x, x1, x3, x0, x2>, list<x, x1, x3, x2, x0>,

      list<x, x2, x0, x1, x3>, list<x, x2, x0, x3, x1>,
      list<x, x2, x1, x0, x3>, list<x, x2, x1, x3, x0>,
      list<x, x2, x3, x0, x1>, list<x, x2, x3, x1, x0>,

      list<x, x3, x0, x1, x2>, list<x, x3, x0, x2, x1>,
      list<x, x3, x1, x0, x2>, list<x, x3, x1, x2, x0>,
      list<x, x3, x2, x0, x1>, list<x, x3, x2, x1, x0>
    >;
  };

  template<>
  struct _permutations<5>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _insert_permutations4::f<x0, x1, x2, x3, x4>,
      _insert_permutations4::f<x1, x2, x3, x4, x0>,
      _insert_permutations4::f<x2, x3, x4, x0, x1>,
      _insert_permutations4::f<x3, x4, x0, x1, x2>,
      _insert_permutations4::f<x4, x0, x1, x2, x3>
    >;
  };

  struct _push_permutations4
  {
    template<class F, class x, class x0, class x1, class x2, class x3>
    using f = list<
      typename F::template f<x, x0, x1, x2, x3>, typename F::template f<x, x0, x1, x3, x2>,
      typename F::template f<x, x0, x2, x1, x3>, typename F::template f<x, x0, x2, x3, x1>,
      typename F::template f<x, x0, x3, x1, x2>, typename F::template f<x, x0, x3, x2, x1>,

      typename F::template f<x, x1, x0, x2, x3>, typename F::template f<x, x1, x0, x3, x2>,
      typename F::template f<x, x1, x2, x0, x3>, typename F::template f<x, x1, x2, x3, x0>,
      typename F::template f<x, x1, x3, x0, x2>, typename F::template f<x, x1, x3, x2, x0>,

      typename F::template f<x, x2, x0, x1, x3>, typename F::template f<x, x2, x0, x3, x1>,
      typename F::template f<x, x2, x1, x0, x3>, typename F::template f<x, x2, x1, x3, x0>,
      typename F::template f<x, x2, x3, x0, x1>, typename F::template f<x, x2, x3, x1, x0>,

      typename F::template f<x, x3, x0, x1, x2>, typename F::template f<x, x3, x0, x2, x1>,
      typename F::template f<x, x3, x1, x0, x2>, typename F::template f<x, x3, x1, x2, x0>,
      typename F::template f<x, x3, x2, x0, x1>, typename F::template f<x, x3, x2, x1, x0>
    >;
  };

  template<class C>
  struct _permutations5
  {
    template<class F, class x0, class x1, class x2, class x3, class x4>
    using f = typename join<C>::template f<
      _push_permutations4::f<F, x0, x1, x2, x3, x4>,
      _push_permutations4::f<F, x1, x2, x3, x4, x0>,
      _push_permutations4::f<F, x2, x3, x4, x0, x1>,
      _push_permutations4::f<F, x3, x4, x0, x1, x2>,
      _push_permutations4::f<F, x4, x0, x1, x2, x3>
    >;
  };

  template<class C>
  struct _permutations6
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename join<C>::template f<
      _permutations5<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5>,
      _permutations5<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x0>,
      _permutations5<listify>::f<push_front<x2, F>, x3, x4, x5, x0, x1>,
      _permutations5<listify>::f<push_front<x3, F>, x4, x5, x0, x1, x2>,
      _permutations5<listify>::f<push_front<x4, F>, x5, x0, x1, x2, x3>,
      _permutations5<listify>::f<push_front<x5, F>, x0, x1, x2, x3, x4>
    >;
  };

  template<>
  struct _permutations<6>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5>
    using f = typename _permutations6<C>::template f<listify, x0, x1, x2, x3, x4, x5>;
  };

  template<class C>
  struct _permutations7
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename join<C>::template f<
      _permutations6<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6>,
      _permutations6<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x0>,
      _permutations6<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x0, x1>,
      _permutations6<listify>::f<push_front<x3, F>, x4, x5, x6, x0, x1, x2>,
      _permutations6<listify>::f<push_front<x4, F>, x5, x6, x0, x1, x2, x3>,
      _permutations6<listify>::f<push_front<x5, F>, x6, x0, x1, x2, x3, x4>,
      _permutations6<listify>::f<push_front<x6, F>, x0, x1, x2, x3, x4, x5>
    >;
  };

  template<>
  struct _permutations<7>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6>
    using f = typename _permutations7<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6>;
  };

#if 0
  template<class C>
  struct _permutations8
  {
    template<class F, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename join<C>::template f<
      _permutations7<listify>::f<push_front<x0, F>, x1, x2, x3, x4, x5, x6, x7>,
      _permutations7<listify>::f<push_front<x1, F>, x2, x3, x4, x5, x6, x7, x0>,
      _permutations7<listify>::f<push_front<x2, F>, x3, x4, x5, x6, x7, x0, x1>,
      _permutations7<listify>::f<push_front<x3, F>, x4, x5, x6, x7, x0, x1, x2>,
      _permutations7<listify>::f<push_front<x4, F>, x5, x6, x7, x0, x1, x2, x3>,
      _permutations7<listify>::f<push_front<x5, F>, x6, x7, x0, x1, x2, x3, x4>,
      _permutations7<listify>::f<push_front<x6, F>, x7, x0, x1, x2, x3, x4, x5>,
      _permutations7<listify>::f<push_front<x7, F>, x0, x1, x2, x3, x4, x5, x6>
    >;
  };

  template<>
  struct _permutations<8>
  {
    template<class C, class x0, class x1, class x2, class x3, class x4, class x5, class x6, class x7>
    using f = typename _permutations8<C>::template f<listify, x0, x1, x2, x3, x4, x5, x6, x7>;
  };
#endif
}
namespace jln::mp
{
  namespace detail
  {
    template<class C, bool>
    struct _powerset;
  }

  template<class C = listify>
  struct powerset
  {
    template<class... xs>
    using f = typename detail::_powerset<C, bool(sizeof...(xs))>
      ::type::template f<list<list<>>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using powerset = unpack<L, mp::powerset<C>>;
  }
}

namespace jln::mp::detail
{
  template<class, class>
  struct _power;

  template<class... xs, class y>
  struct _power<list<xs...>, y>
  {
    using type = list<list<xs...>, list<y, xs...>>;
  };

  template<class, class>
  struct _powerset_impl;

  template<class... seqs, class y>
  struct _powerset_impl<y, list<seqs...>>
  {
    using type = join<>::f<typename _power<seqs, y>::type...>;
  };

  template<class C, bool>
  struct _powerset
  {
    using type = fold_right<cfl<_powerset_impl>, unpack<C>>;
  };

  template<>
  struct _powerset<listify, true>
  {
    using type = fold_right<cfl<_powerset_impl>>;
  };

  template<class C>
  struct _powerset<C, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<>
  struct _powerset<listify, false>
  {
    using type = always<list<>>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _remove_adjacent;
  }

  template<class Cmp, class C = listify>
  struct remove_adjacent_if
  {
    template<class... xs>
    using f = typename detail::_remove_adjacent<
      rotate_c<-1>::template f<xs...>
    >::template f<C, Cmp, xs...>;
  };

  template<class C = listify>
  using remove_adjacent = remove_adjacent_if<same<>, C>;

  namespace emp
  {
    template<class L, class Cmp, class C = mp::listify>
    using remove_adjacent_if = unpack<L, mp::remove_adjacent_if<Cmp, C>>;

    template<class L, class C = mp::listify>
    using remove_adjacent = unpack<L, mp::remove_adjacent<C>>;
  }
}


namespace jln::mp::detail
{
  template<class y, class... ys>
  struct _remove_adjacent<list<y, ys...>>
  {
    template<class C, class Cmp, class x, class... xs>
    using f = typename join<C>::template f<
      list<x>,
      typename list_wrap_if_c<!Cmp::template f<xs, ys>::value>::template f<xs>...>;
  };

  template<class>
  struct _remove_adjacent
  {
    template<class C, class...>
    using f = typename C::template f<>;
  };
}
namespace jln::mp
{
  template<class Pred, class T, class C = listify>
  using replace_if = transform<if_<Pred, always<T>, identity>, C>;

  template<class T, class U, class C = listify>
  using replace = replace_if<same_as<T>, U, C>;

  namespace emp
  {
    template<class L, class T, class U, class C = mp::listify>
    using replace = unpack<L, mp::replace<T, U, C>>;

    template<class L, class Pred, class T, class C = mp::listify>
    using replace_if = unpack<L, mp::replace_if<Pred, T, C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<unsigned>
    struct _reverse;

    constexpr unsigned _rotate_select(unsigned n)
    {
      return (detail::n_8_or_less_16_64_256(n) == n) * 20
        + detail::n_8_or_less_16_64_256(n);
    }
  }

  template<class C = listify>
  struct reverse
  {
    template<class... xs>
    using f = typename detail::_reverse<
      detail::_rotate_select(sizeof...(xs))
    >::template f<C, sizeof...(xs), xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using reverse = unpack<L, mp::reverse<C>>;
  }
}


namespace jln::mp::detail
{
#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)    \
  template<>                                             \
  struct _reverse<n>                                     \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = typename reverse<join<C>>                  \
      ::template f<xs..., list<                          \
        mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                     \
  template<>                                             \
  struct _reverse<n+20>                                  \
  {                                                      \
    template<class C, std::size_t count                  \
      mp_xs(JLN_MP_COMMA class, JLN_MP_NIL, JLN_MP_NIL), \
      class... xs>                                       \
    using f = call<C                                     \
        mp_rxs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>;   \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL

#define JLN_MP_REVERSE_IMPL(n, mp_xs, mp_rxs, mp_rep)  \
  template<>                                           \
  struct _reverse<n>                                   \
  {                                                    \
    template<class C, std::size_t count,               \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                     \
    using f = typename _reverse<                       \
      detail::n_8_or_less_16_64_256(count-n)               \
    >::template f<C, count-n, xs..., list<             \
      mp_rxs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA)>>;  \
  };                                                   \
  template<>                                           \
  struct _reverse<n+20>                                \
  {                                                    \
    template<class C, std::size_t count,               \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),          \
      class... xs>                                     \
    using f = call<C                                   \
        mp_rxs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_8_16_64_256(JLN_MP_REVERSE_IMPL)

#undef JLN_MP_REVERSE_IMPL
}
namespace jln::mp
{
  namespace detail
  {
    template<int n, class Cmp>
    struct _sort;
  }

  template<class Cmp = less<>, class C = listify>
  struct sort
  {
    template<class... xs>
    using f = call<unpack<C>,
      typename detail::_sort<detail::min(3, sizeof...(xs)), Cmp>
      ::template f<xs...>>;
  };

  template<class Cmp = less<>, class C = listify>
  using stable_sort = sort<Cmp, C>;

  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = listify>
    using sort = unpack<L, mp::sort<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = listify>
    using stable_sort = unpack<L, mp::sort<Cmp, C>>;
  }
}


namespace jln::mp
{
  template<class cmp>
  struct as_cmp
  {
    template<class x, class y>
    using f = number<bool(cmp::template f<x, y>::value)>;
  };

  template<class Cmp>
  struct sort<Cmp, listify>
  {
    template<class... xs>
    using f = typename detail::_sort<detail::min(3, sizeof...(xs)), Cmp>
      ::template f<xs...>;
  };
}

namespace jln::mp::detail
{
  template<class Cmp>
  struct _sort<3, Cmp>
  {
    template<class... xs>
    using f = typename memoize_call<_merge<
      call<take_c<sizeof...(xs) / 2, _sort<min(3, sizeof...(xs) / 2), Cmp>>, xs...>,
      call<drop_c<sizeof...(xs) / 2, _sort<min(3, (sizeof...(xs) + 1) / 2), Cmp>>, xs...>
    >, Cmp>::type;
  };

  template<bool>
  struct mk_list2
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct mk_list2<true>
  {
    template<class x, class y>
    using f = list<y, x>;
  };

  template<class Cmp>
  struct _sort<2, Cmp>
  {
    template<class x, class y>
    using f = typename mk_list2<bool(call<Cmp, y, x>::value)>
      ::template f<x, y>;
  };

  template<class Cmp>
  struct _sort<1, Cmp>
  {
    template<class x>
    using f = list<x>;
  };

  template<class Cmp>
  struct _sort<0, Cmp>
  {
    template<class...>
    using f = list<>;
  };
}
namespace jln::mp
{
  template<class Pred, class C = listify>
  struct split_after_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_after, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split_after = split_after_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_after_if = unpack<L, mp::split_after_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_after = unpack<L, mp::split_after<x, C>>;
  }
}
namespace jln::mp
{
  template<class i, class C = listify>
  using split_at = fork<take<i>, drop<i>, C>;

  template<int_ i, class C = listify>
  using split_at_c = split_at<number<i>, C>;

  namespace emp
  {
    template<class L, class i, class C = mp::listify>
    using split_at = unpack<L, mp::split_at<i, C>>;

    template<class L, int_ i, class C = mp::listify>
    using split_at_c = unpack<L, mp::split_at_c<i, C>>;
  }
}
namespace jln::mp
{
  template<class Pred, class C = listify>
  struct split_before_if
  {
    template <class... xs>
    using f = typename detail::_split<sizeof...(xs) != 0>
      ::template f<detail::split_before, C, Pred, xs...>;
  };

  template<class x, class C = listify>
  using split_before = split_before_if<same_as<x>, C>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify>
    using split_before_if = unpack<L, mp::split_before_if<Pred, C>>;

    template<class L, class x, class C = mp::listify>
    using split_before = unpack<L, mp::split_before<x, C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class>
    struct _take_while;
  }

  template<class Pred, class C = listify, class NC = C>
  using take_while = fork_front<index_if<
    Pred, fork<identity, always<C>, cfe<take>>, always<NC>>>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using take_while = unpack<L, mp::take_while<Pred, C, NC>>;
  }
}

namespace jln::mp::detail
{
  template<class n>
  struct _take_while
  {
    template<class C, class NC>
    using f = take<n, C>;
  };

  template<>
  struct _take_while<number<-1>>
  {
    template<class C, class NC>
    using f = NC;
  };
}
namespace jln::mp
{
  template<class x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound = lower_bound<x, flip<fork<Cmp, not_<>>>, C, NC>;

  template<int_ x, class Cmp = less<>, class C = listify, class NC = C>
  using upper_bound_c = upper_bound<number<x>, Cmp, C, NC>;

  template<class x, class C = listify, class NC = C>
  using upper_bound_of = upper_bound<x, less<>, C, NC>;

  template<int_ x, class C = listify, class NC = C>
  using upper_bound_of_c = upper_bound<number<x>, less<>, C, NC>;

  namespace emp
  {
    template<class L, class x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound = unpack<L, mp::upper_bound<x, Cmp, C, NC>>;

    template<class L, int_ x, class Cmp = mp::less<>, class C = mp::listify, class NC = C>
    using upper_bound_c = unpack<L, mp::upper_bound<mp::number<x>, Cmp, C, NC>>;

    template<class L, class x, class C = mp::listify, class NC = C>
    using upper_bound_of = unpack<L, mp::upper_bound<x, mp::less<>, C, NC>>;

    template<class L, int_ x, class C = mp::listify, class NC = C>
    using upper_bound_of_c = unpack<L, mp::upper_bound<mp::number<x>, mp::less<>, C, NC>>;
  }
}
namespace jln::mp::detail
{
  template<class x, class... xs>
#if defined(__GNUC__) and !defined(__clang__)
  using first = x;
#else
  using first = typename conditional_c<0 <= sizeof...(xs)>::template f<x, void>;
#endif
}
namespace jln::mp
{
  template<class F, class... xs>
  struct bind
  {
    template<class... ys>
    using f = call<F, xs..., ys...>;
  };

  template<class F, class... xs>
  struct reverse_bind
  {
    template<class... ys>
    using f = call<F, ys..., xs...>;
  };

  // fork_front<front<F, cfe<push_front, cfe<pop_front>>>, C>
  template<class F, class C>
  struct bind1st
  {
    template<class x, class... xs>
    using f = call<C,
      typename detail::dcall<sizeof...(xs) < 100000>::template f<F, x>, xs...>;
  };

  template<class F, class C>
  struct bind2nd
  {
    template<class x, class y, class... xs>
    using f = call<C, x,
      typename detail::dcall<sizeof...(xs) < 100000>::template f<F, y>, xs...>;
  };
} // namespace jln::mp
namespace jln::mp
{
  template<class... xs>
  struct capture
  {
    template<class C, class... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class... xs>
  struct capture_v
  {
    template<class C, class... ys>
    using f = typename C::template f<xs::value..., ys::value...>;
  };

  template<auto... xs>
  struct capture_c
  {
    template<class C, auto... ys>
    using f = typename C::template f<xs..., ys...>;
  };

  template<class... xs>
  struct reverse_capture
  {
    template<class C, class... ys>
    using f = typename C::template f<ys..., xs...>;
  };

  template<class... xs>
  struct reverse_capture_v
  {
    template<class C, class... ys>
    using f = typename C::template f<ys::value..., xs::value...>;
  };

  template<auto... xs>
  struct reverse_capture_c
  {
    template<class C, auto... ys>
    using f = typename C::template f<ys..., xs...>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<class, class...>
    struct _cascade;
  }

  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}


namespace jln::mp::detail
{
  template<class F, class... Fs>
  struct _cascade
  {
    using type = transform<unpack<typename _cascade<Fs...>::type>, F>;
  };

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F1>, F0>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
namespace jln::mp
{
  template<class N, class C = identity>
  using at = drop<N, front<C>>;

  template<int_ n, class C = identity>
  using at_c = drop<number<n>, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop<number<1>, front<C>>;

  template<class C = identity>
  using at2 = drop<number<2>, front<C>>;

  template<class C = identity>
  using at3 = drop<number<3>, front<C>>;

  template<class C = identity>
  using at4 = drop<number<4>, front<C>>;

  template<class C = identity>
  using at5 = drop<number<5>, front<C>>;

  template<class C = identity>
  using at6 = drop<number<6>, front<C>>;

  template<class C = identity>
  using at7 = drop<number<7>, front<C>>;

  template<class C = identity>
  using at8 = drop<number<8>, front<C>>;

  template<class C = identity>
  using at9 = drop<number<9>, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = unpack<L, mp::drop<number<i::value>, mp::front<C>>>;

    template<class L, int_ i, class C = mp::identity>
    using at_c = unpack<L, mp::drop<number<i>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at0 = unpack<L, mp::front<C>>;

    template<class L, class C = mp::identity>
    using at1 = unpack<L, mp::drop<number<1>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at2 = unpack<L, mp::drop<number<2>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at3 = unpack<L, mp::drop<number<3>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at4 = unpack<L, mp::drop<number<4>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at5 = unpack<L, mp::drop<number<5>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at6 = unpack<L, mp::drop<number<6>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at7 = unpack<L, mp::drop<number<7>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at8 = unpack<L, mp::drop<number<8>, mp::front<C>>>;

    template<class L, class C = mp::identity>
    using at9 = unpack<L, mp::drop<number<9>, mp::front<C>>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<unsigned> struct _compose_f;
    template<class, class> struct _compose;
  }

  template<template<class...> class F, template<class...> class... Fs>
  using compose_f = typename detail::_compose_f<sizeof...(Fs)>
    ::template f<F, Fs...>;

  template<class F, class... Fs>
  using compose = typename conditional_c<sizeof...(Fs) == 0>
    ::template f<
      at1<F>,
      mp::fold_right<cfl<detail::_compose>>
    >
    ::template f<identity, F, Fs...>;
}


namespace jln::mp::detail
{
#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)       \
  template<template<class...> class F                    \
    mp_xs(JLN_MP_COMMA template<class...> class,         \
      JLN_MP_NIL, JLN_MP_NIL)>                           \
  struct _compose_f_impl##n                                \
  {                                                      \
    template<class... xs>                                \
    using f = mp_rxs(JLN_MP_NIL, <, JLN_MP_NIL)          \
      typename detail::dcallf<(sizeof...(xs) < 1000000)> \
      ::template f<F, xs...>                             \
    mp_dup(>, JLN_MP_NIL);                               \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

#define JLN_COMPOSE_IMPL(n, mp_xs, mp_rxs, mp_dup)  \
  template<>                                        \
  struct _compose_f<n>                                \
  {                                                 \
    template<template<class...> class F             \
      mp_xs(JLN_MP_COMMA template<class...> class,  \
        JLN_MP_NIL, JLN_MP_NIL)>                    \
    using f = _compose_f_impl##n<F                    \
      mp_xs(JLN_MP_COMMA, JLN_MP_NIL, JLN_MP_NIL)>; \
  };

  JLN_MP_GEN_XS_0_TO_8(JLN_COMPOSE_IMPL)

#undef JLN_COMPOSE_IMPL

  template<unsigned n>
  struct _compose_f
  {
    template<
      template<class...> class F0,
      template<class...> class F1,
      template<class...> class F2,
      template<class...> class F3,
      template<class...> class F4,
      template<class...> class F5,
      template<class...> class F6,
      template<class...> class F7,
      template<class...> class... Fs>
    using f = typename _compose_f<n-8>::template f<
      _compose_f_impl7<F0, F1, F2, F3, F4, F5, F6, F7>::template f,
      Fs...
    >;
  };

  template<class F, class C>
  struct _compose
  {
    using type = fork<F, C>;
  };

  template<template<class...> class F, class x>
  struct _compose<cfe<F>, x>
  {
    using type = cfe<F, x>;
  };

  template<template<class...> class F, class x>
  struct _compose<cfl<F>, x>
  {
    using type = cfl<F, x>;
  };
}
namespace jln::mp
{
#ifdef __cpp_nontype_template_parameter_class
#if __cpp_nontype_template_parameter_class >= 201806L
  template<auto F, class C = identity>
  struct eval
  {
    template<class... xs>
    using f = typename detail::dcall<sizeof...(xs) + 1>
      ::template f<C, decltype(F.template operator()<xs...>())>;
  };

  namespace emp
  {
    template<auto F, class... xs>
    using eval = decltype(F.template operator()<xs...>());
  }
#endif
#endif
}
namespace jln::mp
{
  template<class C>
  struct fix
  {
    template<class... xs>
    using f = call<C, fix<C>, xs...>;
  };

  namespace emp
  {
    template<class F, class... xs>
    using fix = typename fix<F>::template f<xs...>;
  }
}
namespace jln::mp
{
  template<class F, class C = identity>
  using is_invocable = try_invoke<F, always<true_, C>, always<false_, C>>;

  namespace emp
  {
    template<class F, class... xs>
    using is_invocable = mp::call<mp::is_invocable<F>, xs...>;

    template<class L, class F, class C = mp::identity>
    inline constexpr bool is_invocable_v
      = unpack<L, mp::is_invocable<C>>::value;
  }
}
namespace jln::mp::detail
{
  template<bool>
  struct _monadicify;
}

namespace jln::mp
{
  template<class C, class FC = violation>
  using monadic = if_<same_as<na>, FC, C>;

  template<class C, class FC = violation>
  using monadic0 = if_<front<same_as<na>>, FC, C>;

  template<class C, class FC = violation>
  using monadic_xs = if_<transform<same_as<na>, or_<>>, FC, C>;

  template<class T, class C, class FC = violation>
  using monadic_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic, C, FC>;

  template<class T, class C, class FC = violation>
  using monadic0_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic0, C, FC>;

  template<class T, class C, class FC = violation>
  using monadic_xs_if_na = typename detail::_monadicify<
    std::is_same<na, T>::value>::template f<monadic_xs, C, FC>;
}

namespace jln::mp::detail
{
  template<bool>
  struct _monadicify
  {
    template<template<class, class> class F, class C, class FC>
    using f = F<C, FC>;
  };

  template<>
  struct _monadicify<false>
  {
    template<template<class, class> class F, class C, class FC>
    using f = C;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template <class, class, class...>
    struct _partial_eager;
  }

  template <class... Fs>
  struct partial_eager
  : rotate<number<-2>, cfe<detail::_partial_eager>>
  ::template f<Fs...>::type
  {};

  template <class C>
  struct partial_eager<C>
  {
    template <class... xs>
    using f = call<C, xs...>;
  };

  template <class F, class C>
  struct partial_eager<F, C>
  {
    template <class... xs>
    using f = unary_compose_call<C, F, xs...>;
  };

  template <class F0, class F1, class C>
  struct partial_eager<F0, F1, C>
  {
    template <class x0, class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, call<F0, x0>, call<F1, xs...>>;
  };

  template <class F0, class F1, class F2, class C>
  struct partial_eager<F0, F1, F2, C>
  {
    template <class x0, class x1, class... xs>
    using f = typename detail::dcall<(sizeof...(xs) < 1000000)>
      ::template f<C, call<F0, x0>, call<F1, x1>, call<F2, xs...>>;
  };
}

namespace jln::mp::detail
{
  template <class Flast, class C, class... Fs>
  struct _partial_eager
  {
    using type = fork<
      take_c<sizeof...(Fs), _each<Fs..., listify>>, 
      drop_c<sizeof...(Fs), fork<Flast, listify>>,
      join<C>
    >;
  };
} // namespace jln::mp
namespace jln::mp
{
  namespace detail
  {
    template<class, class>
    struct _recurse;

    template<class>
    struct _recurse_fix;

    template<class F>
    struct _recurse_fix_next;
  }

  template<class>
  struct stop_iteration
  {};

  template<class F, class C = identity>
  struct recurse
  {
    template<class... xs>
    using f = typename detail::_recurse<F, call<F, xs...>>
      ::template f<C>;
  };

  template<class F, class C = identity>
  struct recurse_fix
  {
    template<class... xs>
    using f = typename detail::_recurse_fix<
      typename detail::_recurse_fix_next<F>::template f<xs...>
    >::template f<C>;
  };

  namespace emp
  {
    template<class L, class F, class C = mp::identity>
    using recurse = unpack<L, mp::recurse<F, C>>;

    template<class L, class F, class C = mp::identity>
    using recurse_fix = unpack<L, mp::recurse_fix<F, C>>;
  }
}


namespace jln::mp::detail
{
  template<class F, class x>
  struct _recurse<F, stop_iteration<x>>
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<class x>
  struct _recurse_next
  {
    template<class F>
    using f = typename F::template f<x>;
  };

  template<class x>
  struct _recurse_next<stop_iteration<x>>
  {
    template<class F>
    using f = stop_iteration<x>;
  };

  template<class F, class x>
  struct _recurse
  : _recurse<F,
    typename _recurse_next<
      typename _recurse_next<
        typename _recurse_next<
          typename _recurse_next<
            typename _recurse_next<
              typename _recurse_next<
                typename _recurse_next<
                  typename _recurse_next<
                    typename _recurse_next<
                      typename F::template f<x>
                    >::template f<F>
                  >::template f<F>
                >::template f<F>
              >::template f<F>
            >::template f<F>
          >::template f<F>
        >::template f<F>
      >::template f<F>
    >::template f<F>
  >
  {};

  template<class x>
  struct _recurse_fix<stop_iteration<x>>
  {
    template<class C>
    using f = typename C::template f<x>;
  };

  template<class... xs>
  struct _recurse_capture
  {};

  template<class F>
  struct _bind_recurse
  {
    template<class... xs>
    using f = _recurse_capture<F, xs...>;
  };

  template<class F>
  struct _recurse_fix_next
  {
    struct f0
    {
      template<class... xs>
      using f = call<F, _bind_recurse<F>, xs...>;
    };

    struct f1
    {
      template<class... xs>
      using f = call<F, f0, xs...>;
    };

    struct f2
    {
      template<class... xs>
      using f = call<F, f1, xs...>;
    };

    struct f3
    {
      template<class... xs>
      using f = call<F, f2, xs...>;
    };

    struct f4
    {
      template<class... xs>
      using f = call<F, f3, xs...>;
    };

    struct f5
    {
      template<class... xs>
      using f = call<F, f4, xs...>;
    };

    struct f6
    {
      template<class... xs>
      using f = call<F, f5, xs...>;
    };

    struct f7
    {
      template<class... xs>
      using f = call<F, f6, xs...>;
    };

    struct f8
    {
      template<class... xs>
      using f = call<F, f7, xs...>;
    };

    template<class... xs>
    using f = call<F, f8, xs...>;
  };

  template<class F, class... xs>
  struct _recurse_fix<_recurse_capture<F, xs...>>
  : _recurse_fix<typename _recurse_fix_next<F>::template f<xs...>>
  {};

  template<class x>
  struct _recurse_fix
  {
    template<class C>
    using f = typename C::template f<x>;
  };
}
namespace jln::mp
{
  template<class L, class C = listify>
  using append = push_front<L, unpack_append<C>>;

  namespace emp
  {
    template<class L, class... xs>
    using append = unpack_append<L, listify, xs...>;
  }
}
namespace jln::mp
{
  template<class C = identity>
  using back = rotate<number<-1>, front<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using back = unpack<L, mp::back<C>>;
  }
}
namespace jln::mp
{
  template<class start, class size = number<1>, class C = listify>
  struct erase
  {
    template<class... xs>
    using f = call<
      join<C>,
      typename take<start>::template f<xs...>,
      call<drop_c<std::min<std::size_t>(
        sizeof...(xs),
        detail::validate_index<start::value, sizeof...(xs)>::value
        + std::size_t{size::value}
      )>, xs...>
    >;
  };

  template<int_ start, int_ size = 1, class C = listify>
  using erase_c = erase<number<start>, number<size>, C>;

  namespace emp
  {
    template<class L, class start, class size = mp::number<1>, class C = mp::listify>
    using erase = unpack<L, mp::erase<start, size, C>>;

    template<class L, int_ start, int_ size = 1, class C = mp::listify>
    using erase_c = erase<L, number<start>, number<size>, C>;
  }
}
namespace jln::mp
{
  template<class i, class seq, class C = listify>
  using insert_range = fork<take<i>, always<seq>, drop<i>, join<C>>;

  template<int_ i, class seq, class C = listify>
  using insert_range_c = insert_range<number<i>, seq, C>;

  namespace emp
  {
    template<class L, class i, class seq, class C = mp::listify>
    using insert_range = unpack<L, mp::insert_range<i, seq, C>>;

    template<class L, int_ i, class seq, class C = mp::listify>
    using insert_range_c = unpack<L, mp::insert_range_c<i, seq, C>>;
  }
}
namespace jln::mp
{
  template<class i, class x, class C = listify>
  using insert = insert_range<i, list<x>, C>;

  template<int_ i, class x, class C = listify>
  using insert_c = insert_range_c<i, list<x>, C>;

  namespace emp
  {
    template<class L, class i, class x, class C = mp::listify>
    using insert = unpack<L, mp::insert<i, x, C>>;

    template<class L, int_ i, class x, class C = mp::listify>
    using insert_c = insert<L, number<i>, x, C>;
  }
}
namespace jln::mp
{
  template<class C = identity>
  using is_empty = size<not_<C>>;

  namespace emp
  {
    template<class L, class C = mp::identity>
    using is_empty = unpack<L, mp::is_empty<C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_list;
  }

  template<class C = identity>
  struct is_list
  {
    template<class x>
    using f = typename C::template f<typename detail::_is_list<x>::type>;
  };

  namespace emp
  {
    template<class x, class C = mp::identity>
    using is_list = typename C::template f<typename detail::_is_list<x>::type>;
  }
} // namespace jln::mp


namespace jln::mp::detail
{
  template<class x>
  struct _is_list
  {
    using type = false_;
  };

  template<class... xs>
  struct _is_list<list<xs...>>
  {
    using type = true_;
  };
} // namespace jln::mp::detail
namespace jln::mp
{
  template<class N, class C = identity>
  using is_size_of = size<same_as<N, C>>;

  template<int_ n, class C = identity>
  using is_size_of_c = size<same_as<number<n>, C>>;

  template<class C = identity>
  using is_size_of_1 = is_size_of<number<1>, C>;

  template<class C = identity>
  using is_size_of_2 = is_size_of<number<2>, C>;

  template<class N, class C = identity>
  using is_size_larger_than = size<greater_than<N, C>>;

  template<int_ n, class C = identity>
  using is_size_larger_than_c = size<greater_than<number<n>, C>>;

  namespace emp
  {
    template<class L, class N, class C = mp::identity>
    using is_size_of = unpack<L, mp::is_size_of<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_of_c = unpack<L, mp::is_size_of_c<n, C>>;

    template<class L, class C = mp::identity>
    using is_size_of_1 = unpack<L, is_size_of_1<C>>;

    template<class L, class C = mp::identity>
    using is_size_of_2 = unpack<L, is_size_of_2<C>>;

    template<class L, class N, class C = mp::identity>
    using is_size_larger_than = unpack<L, is_size_larger_than<N, C>>;

    template<class L, int_ n, class C = mp::identity>
    using is_size_larger_than_c = unpack<L, is_size_larger_than_c<n, C>>;
  }
}
namespace jln::mp
{
  template <class I, class C = identity>
  struct offset
  {
    template <class... xs>
    using f = typename C::template f<number<(I::value - int_{sizeof...(xs)})>>;
  };

  template <class I>
  struct offset<I, identity>
  {
    template <class... xs>
    using f = number<(I::value - int_{sizeof...(xs)})>;
  };

  template<int_ i, class C = identity>
  using offset_c = offset<number<i>, C>;

  namespace emp
  {
    template<class L, class I, class C = mp::identity>
    using offset = unpack<L, mp::offset<I, C>>;

    template<class L, int_ i, class C = mp::identity>
    using offset_c = unpack<L, mp::offset<number<i>, C>>;
  }
}
namespace jln::mp
{
  template<class C = listify>
  using pop_back = rotate<number<-1>, pop_front<C>>;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pop_back = unpack<L, mp::pop_back<C>>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<int_ beg, int_ end, class C, bool _
      = !(beg == -1
      || ((beg >= 0 ? end >= 0 : end < 0) && beg >= end)),
      bool = _ && (beg >= 0),
      bool = _ && (end >= 0)>
    struct _range;
  }

  template<class beg, class end, class C = listify>
  struct range : detail::_range<beg::value, end::value, C>::type
  {
    // TODO doc
    // template<class... xs>
    // using f;
  };

  template<int_ beg, int_ end, class C = listify>
  using range_c = typename detail::_range<beg, end, C>::type;

  namespace emp
  {
    template<class L, class beg, class end, class C = mp::listify>
    using range = unpack<L, mp::range<beg, end, C>>;

    template<class L, int_ beg, int_ end, class C = mp::listify>
    using range_c = unpack<L, mp::range_c<beg, end, C>>;
  }
}

namespace jln::mp::detail
{
  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, false, false, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<int_ beg, int_ end>
  struct _range<beg, end, listify, false, false, false>
  {
    using type = always<list<>>;
  };

  template<class C>
  struct _range<0, -1, C, true, true, false>
  {
    using type = C;
  };

  template<int_ beg, int_ end, class C, bool b1, bool b2>
  struct _range<beg, end, C, true, b1, b2>
  {
    struct impl
    {
      template<class... xs>
      using f = typename range_c<
        (beg >= 0
          ? beg
          : (sizeof...(xs) <= -beg
            ? 0
            : int_(sizeof...(xs)) + beg)),
        (end >= 0
          ? end
          : (sizeof...(xs) <= -end
            ? 0
            : int_(sizeof...(xs)) + (end+1))),
        C
      >::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, int_ end, int_ n, class C,
    bool = (beg < n), bool = (end < n)>
  struct _range_impl // true, true
  {
    using type = drop_c<beg, take_c<end - beg, C>>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, true>
  {
    using type = take_c<end, C>;
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, true, false>
  {
    using type = drop_c<beg, C>;
  };

  template<int_ end, int_ n, class C>
  struct _range_impl<0, end, n, C, true, false>
  {
    using type = C;
  };

  template<int_ beg, int_ end, int_ n, class C>
  struct _range_impl<beg, end, n, C, false, false>
  {
    using type = _cartesian<C, 0>; // for C::f<>
  };

  template<int_ beg, int_ end, int_ n>
  struct _range_impl<beg, end, n, listify, false, false>
  {
    using type = always<list<>>;
  };

  template<int_ beg, int_ end, class C>
  struct _range<beg, end, C, true, true, true>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, end, sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };

  template<int_ beg, class C>
  struct _range<beg, -1, C, true, true, false>
  {
    struct impl
    {
      template<class... xs>
      using f = typename _range_impl<beg, sizeof...(xs), sizeof...(xs), C>
        ::type::template f<xs...>;
    };

    using type = impl;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<int>
    struct _slice;

    constexpr int_ slide_select(int_ nx, int_ size, int_ stride)
    {
      return !size ? 0
        : size == 1 ? 3
        : stride <= 1 ? 2
        : nx < stride ? 2
        : 1;
    }
  }

  template<class start, class size, class stride = number<1>, class C = listify>
  struct slice
  {
    template<class... xs>
    using f = typename detail::_slice<
      detail::slide_select(int_(sizeof...(xs)) - start::value, size::value, stride::value)
    >
    ::template f<
      start::value, size::value,
      // verify that stride is strictly greater than 0
      unsigned{int_(stride::value)-1}+1u,
      C, sizeof...(xs)>
    ::template f<xs...>;
  };

  template<unsigned start, unsigned size, unsigned stride = 1, class C = listify>
  using slice_c = slice<number<start>, number<size>, number<stride>, C>;

  namespace emp
  {
    template<class L, class start, class size, class stride = number<1>, class C = mp::listify>
    using slice = unpack<L, slice<start, size, stride, C>>;

    template<class L, unsigned start, unsigned size, unsigned stride = 1, class C = mp::listify>
    using slice_c = slice<L, number<start>, number<size>, number<stride>, C>;
  }
}


namespace jln::mp::detail
{
  template<>
  struct _slice<2>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = drop_c<start, take_c<
      detail::validate_index<size - 1u,
        unsigned{int_(len) - start}>::value + 1u,
      C>>;
  };

  template<unsigned size, unsigned stride, class C>
  struct _slice_impl
  {
    template<int_... ints>
    struct impl
    {
      template<class... xs>
      using f = typename join<C>::template f<
        typename list_wrap_if_c<(ints <= size && ints % stride == 0)>
        ::template f<xs>
      ...>;
    };
  };

  template<>
  struct _slice<1>
  {
    template<unsigned start, unsigned size, unsigned stride, class C, unsigned len>
    using f = drop_c<
      start,
      typename emp::make_int_sequence_v_c<
        detail::validate_index<int_(len) - start, len>::value,
        cfe_c<_slice_impl<
          detail::validate_index<size * stride - stride + 1, len - start>::value,
          stride, C
        >::template impl>
      >
    >;
  };

  template<>
  struct _slice<0>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = typename conditional_c<
      bool(detail::validate_index<start, len>::value)
    >::template f<C, C>;
  };

  template<>
  struct _slice<3>
  {
    template<unsigned start, unsigned size, unsigned /*stride*/, class C, unsigned len>
    using f = drop_c<start, front<C>>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    constexpr int_ sliding_stride(int_ size, int_ stride);

    template<int_ size, int_ stride, int_ = sliding_stride(size, stride)>
    struct mk_sliding;
  }

  template<class size, class stride = number<1>, class C = listify>
  using sliding = typename detail::mk_sliding<size::value, stride::value>::template f<C>;

  template<int_ size, int_ stride = 1, class C = listify>
  using sliding_c = typename detail::mk_sliding<size, stride>::template f<C>;

  namespace emp
  {
    template<class L, class size, class stride = number<1>, class C = mp::listify>
    using sliding = unpack<L, mp::sliding<size, stride, C>>;

    template<class L, int_ size, int_ stride = 1, class C = mp::listify>
    using sliding_c = unpack<L, mp::sliding_c<size, stride, C>>;
  }
}


namespace jln::mp::detail
{
  constexpr int_ sliding_stride(int_ size, int_ stride)
  {
    if (!stride || size < 1) {
      return size == 0 ? -2 : -1;
    }

    if (stride < 0) {
      stride += size;
      if (stride <= 0) {
        return -1;
      }
    }

    return stride;
  }

  template<int>
  struct _sliding;

  constexpr int sliding_select(int n, int_ size, int_ stride);

  template<int_ size, int_ stride, class C>
  struct sliding_
  {
    template<class... xs>
    using f = typename detail::_sliding<detail::sliding_select(
      sizeof...(xs), size, stride)
    >::template f<C, size, stride, xs...>;
  };

  template<int_ size, int_, int_ stride>
  struct mk_sliding
  {
    template<class C>
    using f = sliding_<size, stride, optimize_useless_transform_unpack_t<C>>;
  };

  // TODO generic class for error
  template<class C>
  struct sliding_nostride
  {};

  template<class C>
  struct sliding_0size
  {
    template<class... xs>
    using f = typename dcall<sizeof...(xs) < 100000>::template f<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -1>
  {
    template<class C>
    using f = sliding_nostride<C>;
  };

  template<int_ size, int_ stride>
  struct mk_sliding<size, stride, -2>
  {
    template<class C>
    using f = sliding_0size<C>;
  };

  constexpr int_ slinding_pivot(int_ nx, int_ size, int_ stride)
  {
    return nx - (nx - size + stride - 1) / stride * stride - 1;
  }

  constexpr int sliding_select(int n, int_ size, int_ stride)
  {
    return n <= size ? (n ? 1 : 0)         // C<list<xs...>>
      : size == 1 ? (stride == 1 ? 2 : 3)  // C<list<xs>...> / slice<0, n/stride, stride>
      : stride > n ? 9                     // take
      : stride == 1 ? (size == 2 ? 4 : 5)  // common case
      : stride == size ? 6                 // group_n
      // slice<zip_longest> / slice<zip>
      : ((n - size) % stride) ? (slinding_pivot(n, size, stride)  < 0  ?  7 : 8) : 7;
  }

  template<>
  struct _sliding<-1>
  {};

  template<>
  struct _sliding<0>
  {
    template<class C, int_, int_, class...>
    using f = typename C::template f<>;
  };

  template<>
  struct _sliding<1>
  {
    template<class C, int_, int_, class... xs>
    using f = typename C::template f<list<xs...>>;
  };

  template<>
  struct _sliding<2>
  {
    template<class C, int_, int_, class... xs>
    using f = typename C::template f<list<xs>...>;
  };

  template<>
  struct _sliding<3>
  {
    template<class C, int_, int_ stride, class... xs>
    using f = typename _slice<1>
      ::template f<0, (sizeof...(xs) + stride - 1) / stride, stride, transform<listify, C>, sizeof...(xs)>
      ::template f<xs...>;
  };

  template<>
  struct _sliding<4>
  {
    template<class C, int_, int_, class x, class... xs>
    using f = typename _zip_impl<
      C,
      mp::rotate_c<-1, drop_c<1>>::f<x, xs...>,
      list<xs...>
    >::type;
  };

  template<>
  struct _sliding<5>
  {
    template<class C, int_ size, class drop>
    struct impl
    {
      template<int_... i>
      using f = _fork<zip<C>, rotate_c<i-size, drop>...>;
    };

    template<class C, int_ size, int_, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<C, size-1, drop_c<size-1>>>,
      number<size>
    >::template f<xs...>;
  };

  template<>
  struct _sliding<6>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename emp::make_int_sequence_v_c<
      sizeof...(xs), cfe_c<_group_n_impl>
    >::template f<C, size, xs...>;
  };

  template<>
  struct _sliding<7>
  {
    template<class C, int_ size, int_ stride>
    struct impl
    {
      template<size_t... i>
      using f = _fork<zip<C>, slice_c<i, size, stride>...>;
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<C, (sizeof...(xs) - size) / stride + 1, stride>>,
      number<size>
    >::template f<xs...>;
  };

  constexpr int_ slinding8_pivot(int_ nx, int_ size, int_ stride)
  {
    int_ r = slinding_pivot(nx, size, stride);
    return r < 0 ? size : r;
  }

  template<>
  struct _sliding<8>
  {
    template<class F, class C>
    struct adjust
    {
      template<class x, class... xs>
      using f = typename C::template f<xs..., typename F::template f<x>>;
    };

    template<class C, int_ size, int_ stride, int_ pivot>
    struct impl
    {
      template<int_... i>
      using f = _fork<zip<
        rotate_c<-1, adjust<unpack<rotate_c<-1, pop_front<>>>, C>>
      >, slice_c<i, size - (pivot < i), stride,
        typename conditional_c<(pivot < i)>::template f<push_back<void>, listify>
      >...>;
    };

    template<class C, int_ size, int_ stride, class... xs>
    using f = typename memoize_call<
      make_int_sequence_v<impl<
        C,
        (sizeof...(xs) - size) / stride + 2,
        stride,
        slinding8_pivot(sizeof...(xs), size, stride)
      >>,
      number<size>
    >::template f<xs...>;
  };

  template<>
  struct _sliding<9>
  {
    template<class C, int_ size, int_, class... xs>
    using f = typename C::template f<typename take_c<size>::template f<xs...>>;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<unsigned i, unsigned j, bool = (i < j), bool = (i == j)>
    struct _select_swap_index;
  }

  template<class I, class J, class C = listify>
  using swap_index = typename detail::_select_swap_index<
    unsigned{I::value}, unsigned{J::value}>::template f<C>;

  template<unsigned i, unsigned j, class C = listify>
  using swap_index_c = typename detail::_select_swap_index<
    i, j>::template f<C>;

  namespace emp
  {
    template<class L, class I, class J, class C = mp::listify>
    using swap_index = unpack<L, swap_index<I, J, C>>;

    template<class L, unsigned i, unsigned j, class C = mp::listify>
    using swap_index_c = unpack<L, swap_index_c<i, j, C>>;
  }
}


namespace jln::mp::detail
{
  template<unsigned i, unsigned j, class C>
  struct swap_elem
  {
    template<class... xs>
    using f = typename join<C>::template f<
      call<take_c<i>, xs...>,
      list<call<at_c<j>, xs...>>,
      call<drop_c<i+1, take_c<j-i-1>>, xs...>,
      list<call<at_c<i>, xs...>>,
      call<drop_c<j+1>, xs...>
    >;
  };

  template<unsigned i, unsigned j, bool, bool>
  struct _select_swap_index
  {
    template<class C>
    using f = swap_elem<i, j, C>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, false>
  {
    template<class C>
    using f = swap_elem<j, i, C>;
  };

  template<unsigned i, class C>
  struct if_valid_index
  {
    template<class... xs>
    using f = typename detail::dcall<
      (unsigned{int(sizeof...(xs)) - int{i}} < 1000000)
    >::template f<C, xs...>;
  };

  template<unsigned i, unsigned j>
  struct _select_swap_index<i, j, false, true>
  {
    template<class C>
    using f = if_valid_index<i, C>;
  };
}
namespace jln::mp
{
  template<class C = identity>
  struct as_bool
  {
    template<class x>
    using f = call<C, number<bool{x::value}>>;
  };

  namespace emp
  {
    template<class x>
    using as_bool = number<bool{x::value}>;
  }
}
namespace jln::mp
{
  template<class C = identity>
  struct as_number
  {
    template<class x>
    using f = call<C, number<x::value>>;
  };

  namespace emp
  {
    template<class x>
    using as_number = number<x::value>;
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_number;
  }

  template<class C = identity>
  struct is_number
  {
    template<class x>
    using f = call<C, typename detail::_is_number<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using is_number = typename detail::_is_number<x>::type;
  }
}


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
}
namespace jln::mp
{
  namespace detail
  {
    struct _pow;
  }

  template<class Cmp = less<>, class C = identity>
  using min = fold_left<if_<flip<Cmp>, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using min0 = if_<size<>, min<Cmp, C>, always<number<0>, C>>;


  template<class Cmp = less<>, class C = identity>
  using max = fold_left<if_<Cmp, at1<>, at0<>>, C>;

  template<class Cmp = less<>, class C = identity>
  using max0 = if_<size<>, max<Cmp, C>, always<number<0>, C>>;


  template<class Min, class Max, class Cmp = less<>, class C = identity>
  using clamp = if_<push_back<Min, Cmp>, always<Min>,
    if_<push_front<Max, Cmp>, always<Max>, identity>>;

  template<int_ min, int_ max, class Cmp = less<>, class C = identity>
  using clamp_c = clamp<number<min>, number<max>, Cmp, C>;


  template<class Cmp = less<>, class C = identity>
  using abs = fork<identity, neg<>, max<Cmp, C>>;


  template<class C = identity>
  using pow = fold_left<detail::_pow, C>;

  template<class C = identity>
  using pow0 = if_<size<>, pow<C>, always<number<0>, C>>;

  template<class C = identity>
  using pow1 = if_<size<>, pow<C>, always<number<1>, C>>;


  namespace emp
  {
    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min = unpack<L, mp::min<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using min0 = unpack<L, mp::min0<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max = unpack<L, mp::max<Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using max0 = unpack<L, mp::max0<Cmp, C>>;

    template<class L, class Min, class Max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp = unpack<L, mp::clamp<Min, Max, Cmp, C>>;

    template<class L, int_ min, int_ max, class Cmp = mp::less<>, class C = mp::identity>
    using clamp_c = unpack<L, mp::clamp_c<min, max, Cmp, C>>;

    template<class L, class Cmp = mp::less<>, class C = mp::identity>
    using abs = unpack<L, mp::abs<Cmp, C>>;

    template<class L, class C = mp::identity>
    using pow = unpack<L, mp::pow<C>>;

    template<class L, class C = mp::identity>
    using pow0 = unpack<L, mp::pow0<C>>;

    template<class L, class C = mp::identity>
    using pow1 = unpack<L, mp::pow1<C>>;
  }
}

namespace jln::mp::detail
{
  template<int_ b, int_ e, int_ r = 1>
  struct _ipow
  : _ipow<(b * b), (e / 2), (e % 2 ? b * r : r)>
  {};

  struct _pow
  {
    template<class base, class exponent>
    using f = typename _ipow<base::value, exponent::value, 1>::type;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 0, r>
  {
    using type = number<1>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, 1, r>
  {
    using type = number<b * r>;
  };

  template<int_ b, int_ r>
  struct _ipow<b, -1, r>
  {
    using type = number<1 / (b * r)>;
  };

  template<int_ r>
  struct _ipow<0, -1, r>
  {};
}
namespace jln::mp
{
  namespace detail
  {
    template<class x, class = void>
    struct _has_type;
  }

  template<class C = identity>
  struct has_type
  {
    template<class x>
    using f = typename C::template f<
      typename detail::_has_type<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using has_type = typename detail::_has_type<x>::type;

    template<class x>
    inline constexpr bool has_type_v = detail::_has_type<x>::type::value;
  }
}

namespace jln::mp::detail
{
  template<class x, class>
  struct _has_type
  {
    using type = false_;
  };

  template<class x>
  struct _has_type<x, std::void_t<typename x::type>>
  {
    using type = true_;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<template<class...> class Tpl, class T>
    struct _is_instance_of;
  }

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
namespace jln::mp
{
  template<class C = identity>
  struct is_same
  {
    template<class x, class y>
    using f = number<std::is_same<x, y>::value>;
  };

  // TODO is_instance_of<list>
}
namespace jln::mp
{
#if __cplusplus >= 201703L
# if !JLN_MP_ENABLE_DEBUG || defined(__clang__)
  template<auto v>
  struct val
  {
    static constexpr decltype(v) const value = v;
  };

  template<class T, T v>
  using typed_val = val<v>;
# else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };

  template<auto v>
  using val = typed_val<std::remove_const_t<decltype(v)>, v>;
# endif
#else
  template<class T, T v>
  struct typed_val
  {
    static constexpr T const value = v;
  };
#endif
}
namespace jln::mp
{
  template<class C = identity>
  struct as_val
  {
    template<class x>
#if __cplusplus >= 201703L
    using f = mp::call<C, val<x::value>>;
#else
    using f = mp::call<C, typed_value<decltype(x::value), x::value>>;
#endif
  };

  namespace emp
  {
    template<class x>
#if __cplusplus >= 201703L
    using f = val<x::value>;
#else
    using f = typed_value<decltype(x::value), x::value>;
#endif
  }
}
namespace jln::mp
{
  namespace detail
  {
    template<class x, class = void>
    struct _has_value;
  }

  template<class C = identity>
  struct has_value
  {
    template<class x>
    using f = typename C::template f<
      typename detail::_has_value<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using has_value = typename detail::_has_value<x>::type;

    template<class x>
    inline constexpr bool has_value_v = detail::_has_value<x>::type::value;
  }
}

namespace jln::mp::detail
{
  template<class x, class>
  struct _has_value
  {
    using type = false_;
  };

  template<class x>
  struct _has_value<x, decltype(void(x::value))>
  {
    using type = true_;
  };
}
namespace jln::mp
{
  namespace detail
  {
    template<class x>
    struct _is_val;
  }

  template<class C = identity>
  struct is_val
  {
    template<class x>
    using f = call<C, typename detail::_is_val<x>::type>;
  };

  namespace emp
  {
    template<class x>
    using is_val = typename detail::_is_val<x>::type;
  }
}


namespace jln::mp::detail
{
  template<class x>
  struct _is_val
  {
    using type = false_;
  };

#if __cplusplus >= 201703L
  template<auto x>
  struct _is_val<val<x>>
#else
  template<class T, T x>
  struct _is_val<typed_value<T, x>>
#endif
  {
    using type = true_;
  };
}
JLN_DIAGNOSTIC_PUSH
JLN_DIAGNOSTIC_GCC_ONLY_IGNORE("-Wlogical-op")

namespace jln::mp
{
  template<class C = identity>
  struct or_v
  {
    template<class... xs>
    using f = typename C::template f<val<(false || ... || xs::value)>>;
  };

  template<class C = identity>
  struct and_v
  {
    template<class... xs>
    using f = typename C::template f<val<(true && ... && xs::value)>>;
  };

  template<class C = identity>
  struct add_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... + xs::value)>>;
  };

  template<class C = identity>
  using add0_v = if_<size<>, add_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct sub_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... - xs::value)>>;
  };

  template<class C = identity>
  using sub0_v = if_<size<>, sub_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct lshift_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... << xs::value)>>;
  };

  template<class C = identity>
  using lshift0_v = if_<size<>, lshift_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct rshift_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... >> xs::value)>>;
  };

  template<class C = identity>
  using rshift0_v = if_<size<>, rshift_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct mul_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... * xs::value)>>;
  };

  template<class C = identity>
  using mul0_v = if_<size<>, mul_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using mul1_v = if_<size<>, mul_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct div_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... / xs::value)>>;
  };

  template<class C = identity>
  using div0_v = if_<size<>, div_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using div1_v = if_<size<>, div_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct mod_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... %  xs::value)>>;
  };

  template<class C = identity>
  using mod0_v = if_<size<>, mod_v<C>, always<val<0>, C>>;

  template<class C = identity>
  using mod1_v = if_<size<>, mod_v<C>, always<val<1>, C>>;

  template<class C = identity>
  struct xor_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... ^ xs::value)>>;
  };

  template<class C = identity>
  using xor0_v = if_<size<>, xor_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct bit_and_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... & xs::value)>>;
  };

  template<class C = identity>
  using bit_and0_v = if_<size<>, bit_and_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct bit_or_v
  {
    template<class... xs>
    using f = typename C::template f<val<(... | xs::value)>>;
  };

  template<class C = identity>
  using bit_or0_v = if_<size<>, bit_or_v<C>, always<val<0>, C>>;

  template<class C = identity>
  struct neg_v
  {
    template<class x>
    using f = typename C::template f<val<(-x::value)>>;
  };

  template<class C = identity>
  struct unary_plus_v
  {
    template<class x>
    using f = typename C::template f<val<(+x::value)>>;
  };

  template<class C = identity>
  struct not_v
  {
    template<class x>
    using f = typename C::template f<val<(!x::value)>>;
  };

  template<class C = identity>
  struct bit_not_v
  {
    template<class x>
    using f = typename C::template f<val<(~x::value)>>;
  };

  template<class C = identity>
  struct inc_v
  {
    template<class x>
    using f = typename C::template f<val<(x::value+1)>>;
  };

  template<class C = identity>
  struct dec_v
  {
    template<class x>
    using f = typename C::template f<val<(x::value-1)>>;
  };

  template<class C = identity>
  struct equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value == y::value)>>;
  };

  template<class C = identity>
  struct not_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value != y::value)>>;
  };

  template<class C = identity>
  struct less_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value < y::value)>>;
  };

  template<class C = identity>
  struct less_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value <= y::value)>>;
  };

  template<class C = identity>
  struct greater_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value > y::value)>>;
  };

  template<class C = identity>
  struct greater_equal_v
  {
    template<class x, class y>
    using f = typename C::template f<val<(x::value >= y::value)>>;
  };


  template<class N, class C = identity>
  using equal_than_v = push_back<N, equal_v<C>>;

  template<class N, class C = identity>
  using not_equal_than_v = push_back<N, not_equal_v<C>>;

  template<class N, class C = identity>
  using less_than_v = push_back<N, less_v<C>>;

  template<class N, class C = identity>
  using less_equal_than_v = push_back<N, less_equal_v<C>>;

  template<class N, class C = identity>
  using greater_than_v = push_back<N, greater_v<C>>;

  template<class N, class C = identity>
  using greater_equal_than_v = push_back<N, greater_equal_v<C>>;


  template<auto x, class C = identity>
  using equal_than_c_v = equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using not_equal_than_c_v = not_equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_than_c_v = less_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_equal_than_c_v = less_equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_than_c_v = greater_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_equal_than_c_v = greater_equal_than_v<val<x>, C>;
}

namespace jln::mp::emp
{
  template<class L, class C = mp::identity>
  using or_seq_v = unpack<L, mp::or_v<C>>;

  template<class L, class C = mp::identity>
  using and_seq_v = unpack<L, mp::and_v<C>>;

  template<class L, class C = mp::identity>
  using add_seq_v = unpack<L, mp::add_v<C>>;

  template<class L, class C = mp::identity>
  using add0_seq_v = unpack<L, mp::add0_v<C>>;

  template<class L, class C = mp::identity>
  using sub_seq_v = unpack<L, mp::sub_v<C>>;

  template<class L, class C = mp::identity>
  using sub0_seq_v = unpack<L, mp::sub0_v<C>>;

  template<class L, class C = mp::identity>
  using lshift_seq_v = unpack<L, mp::lshift_v<C>>;

  template<class L, class C = mp::identity>
  using lshift0_seq_v = unpack<L, mp::lshift0_v<C>>;

  template<class L, class C = mp::identity>
  using rshift_seq_v = unpack<L, mp::rshift_v<C>>;

  template<class L, class C = mp::identity>
  using rshift0_seq_v = unpack<L, mp::rshift0_v<C>>;

  template<class L, class C = mp::identity>
  using mul_seq_v = unpack<L, mp::mul_v<C>>;

  template<class L, class C = mp::identity>
  using mul0_seq_v = unpack<L, mp::mul0_v<C>>;

  template<class L, class C = mp::identity>
  using mul1_seq_v = unpack<L, mp::mul1_v<C>>;

  template<class L, class C = mp::identity>
  using div_seq_v = unpack<L, mp::div_v<C>>;

  template<class L, class C = mp::identity>
  using div0_seq_v = unpack<L, mp::div0_v<C>>;

  template<class L, class C = mp::identity>
  using div1_seq_v = unpack<L, mp::div1_v<C>>;

  template<class L, class C = mp::identity>
  using mod_seq_v = unpack<L, mp::mod_v<C>>;

  template<class L, class C = mp::identity>
  using mod0_seq_v = unpack<L, mp::mod0_v<C>>;

  template<class L, class C = mp::identity>
  using mod1_seq_v = unpack<L, mp::mod1_v<C>>;

  template<class L, class C = mp::identity>
  using xor_seq_v = unpack<L, mp::xor_v<C>>;

  template<class L, class C = mp::identity>
  using xor0_seq_v = unpack<L, mp::xor0_v<C>>;

  template<class L, class C = mp::identity>
  using bit_and_seq_v = unpack<L, mp::bit_and_v<C>>;

  template<class L, class C = mp::identity>
  using bit_and0_seq_v = unpack<L, mp::bit_and0_v<C>>;

  template<class L, class C = mp::identity>
  using bit_or_seq_v = unpack<L, mp::bit_or_v<C>>;

  template<class L, class C = mp::identity>
  using bit_or0_seq_v = unpack<L, mp::bit_or0_v<C>>;


  template<auto... xs>
  using or_c_v = val<(false || ... || xs)>;

  template<auto... xs>
  using and_c_v = val<(true && ... && xs)>;

  template<auto... xs>
  using add_c_v = val<(... + xs)>;

  template<auto... xs>
  using add0_c_v = add_c_v<xs..., 0>;

  template<auto... xs>
  using sub_c_v = val<(... - xs)>;

  template<auto... xs>
  using sub0_c_v = sub_c_v<xs..., 0>;

  template<auto... xs>
  using lshift_c_v = val<(... << xs)>;

  template<auto... xs>
  using lshift0_c_v = lshift_c_v<xs..., 0>;

  template<auto... xs>
  using rshift_c_v = val<(... >> xs)>;

  template<auto... xs>
  using rshift0_c_v = rshift_c_v<xs..., 0>;

  template<auto... xs>
  using mul_c_v = val<(... * xs)>;

  template<auto... xs>
  using mul0_c_v = mul_c_v<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using mul1_c_v = mul_c_v<xs..., 1>;

  template<auto... xs>
  using div_c_v = val<(... / xs)>;

  template<auto... xs>
  using div0_c_v = div_c_v<xs..., (sizeof...(xs) ? 1 : 0)>;

  template<auto... xs>
  using div1_c_v = div_c_v<xs..., 1>;

  template<auto... xs>
  using mod_c_v = val<(... % xs)>;
}

namespace jln::mp::detail
{
  template<bool, template<auto...> class f, int_ d>
  struct _emp_op_v;

  template<template<auto...> class F, int_ d>
  struct _emp_op_v<true, F, d>
  {
    template<auto... xs>
    using f = F<xs...>;
  };

  template<template<auto...> class F, int_ d>
  struct _emp_op_v<false, F, d>
  {
    template<auto...>
    using f = val<d>;
  };
}

namespace jln::mp::emp
{
  template<auto... xs>
  using mod0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, mod_c_v, 0>
    ::template f<xs...>;

  template<auto... xs>
  using mod1_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, mod_c_v, 1>
    ::template f<xs...>;

  template<auto... xs>
  using xor_c_v = val<(... ^ xs)>;

  template<auto... xs>
  using xor0_c_v = xor_c_v<xs..., 0, 0>;

  template<auto... xs>
  using bit_and_c_v = val<(... & xs)>;

  template<auto... xs>
  using bit_and0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, bit_and_c_v, 0>
    ::template f<xs...>;

  template<auto... xs>
  using bit_or_c_v = val<(... | xs)>;

  template<auto... xs>
  using bit_or0_c_v = typename detail::_emp_op_v<sizeof...(xs) != 0, bit_or_c_v, 0>
    ::template f<xs...>;


  template<class... xs>
  using or_v = val<(false || ... || xs::value)>;

  template<class... xs>
  using and_v = val<(true && ... && xs::value)>;

  template<class... xs>
  using add_v = val<(... + xs::value)>;

  template<class... xs>
  using add0_v = call<mp::add0_v<>, xs...>;

  template<class... xs>
  using sub_v = val<(... - xs::value)>;

  template<class... xs>
  using sub0_v = call<mp::sub0_v<>, xs...>;

  template<class... xs>
  using lshift_v = val<(... << xs::value)>;

  template<class... xs>
  using lshift0_v = call<mp::lshift0_v<>, xs...>;

  template<class... xs>
  using rshift_v = val<(... >> xs::value)>;

  template<class... xs>
  using rshift0_v = call<mp::rshift0_v<>, xs...>;

  template<class... xs>
  using mul_v = val<(... * xs::value)>;

  template<class... xs>
  using mul0_v = call<mp::mul0_v<>, xs...>;

  template<class... xs>
  using mul1_v = call<mp::mul1_v<>, xs...>;

  template<class... xs>
  using div_v = val<(... / xs::value)>;

  template<class... xs>
  using div0_v = call<mp::div0_v<>, xs...>;

  template<class... xs>
  using div1_v = call<mp::div1_v<>, xs...>;

  template<class... xs>
  using mod_v = val<(... % xs::value)>;

  template<class... xs>
  using mod0_v = call<mp::mod0_v<>, xs...>;

  template<class... xs>
  using mod1_v = call<mp::mod1_v<>, xs...>;

  template<class... xs>
  using xor_v = val<(... ^ xs::value)>;

  template<class... xs>
  using xor0_v = call<mp::xor0_v<>, xs...>;

  template<class... xs>
  using bit_and_v = val<(... & xs::value)>;

  template<class... xs>
  using bit_and0_v = call<mp::bit_and0_v<>, xs...>;

  template<class... xs>
  using bit_or_v = val<(... | xs::value)>;

  template<class... xs>
  using bit_or0_v = call<mp::bit_or0_v<>, xs...>;


  template<class x, class C = mp::identity>
  using neg_v = call<mp::neg_v<C>, x>;

  template<class x, class C = mp::identity>
  using unary_plus_v = call<mp::unary_plus_v<C>, x>;

  template<class x, class C = mp::identity>
  using not_v = call<mp::not_v<C>, x>;

  template<class x, class C = mp::identity>
  using bit_not_v = call<mp::bit_not_v<C>, x>;

  template<class x, class C = mp::identity>
  using inc_v = call<mp::inc_v<C>, x>;

  template<class x, class C = mp::identity>
  using dec_v = call<mp::dec_v<C>, x>;

  template<class x, class y, class C = mp::identity>
  using equal_v = call<mp::equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using not_equal_v = call<mp::not_equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_v = call<mp::less_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using less_equal_v = call<mp::less_equal_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_v = call<mp::greater_v<C>, x, y>;

  template<class x, class y, class C = mp::identity>
  using greater_equal_v = call<mp::greater_equal_v<C>, x, y>;
}

JLN_DIAGNOSTIC_POP
#if __cplusplus >= 201703L
namespace jln::mp
{
  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = call<C, val<xs::value>...>;
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = call<C, val<T(xs::value)>...>;
  };

  namespace emp
  {
    template<auto... xs>
    using values = list<val<xs>...>;

    template<class T, T... xs>
    using typed_values = list<val<T(xs)>...>;
  }
} // namespace jln::mp
#else
namespace jln::mp
{
  template<class C>
  struct values
  {
    template<class... xs>
    using f = call<C, typed_val<decltye(xs::value), xs::value>...>;
  };

  template<class C>
  struct typed_values
  {
    template<class x, class... xs>
    using f = call<C, x, typed_val<x, xs::value>...>;
  };

  namespace emp
  {
    template<class T, T... xs>
    using typed_values = list<typed_val<T, xs>...>;
  }
}
#endif


