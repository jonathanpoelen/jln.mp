#pragma once

#include <jln/mp/functional/memoize.hpp>
#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/config/debug.hpp>

#define JLN_MP_IDENT(...) __VA_ARGS__

#if ! JLN_MP_ENABLE_DEBUG || JLN_MP_MSVC
  #define JLN_MP_TRACE_F(...) __VA_ARGS__

  #define JLN_MP_CALL_TRACE(C, ...) typename JLN_MP_IDENT C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_T(C, ...) typename JLN_MP_IDENT C ::template f<__VA_ARGS__>
  #define JLN_MP_CALL_TRACE_0_ARG(...) typename __VA_ARGS__::template f<>
#else
  // does not compile with msvc...
  #define JLN_MP_TRACE_F(...) memoize<__VA_ARGS__>

  #define JLN_MP_CALL_TRACE(C, ...)                \
    typename ::jln::mp::detail::memoizer_impl<     \
      JLN_MP_IDENT C, ::jln::mp::list<__VA_ARGS__> \
    >::type
  #define JLN_MP_CALL_TRACE_T(C, ...)                       \
    typename ::jln::mp::detail::memoizer_impl<              \
      typename JLN_MP_IDENT C, ::jln::mp::list<__VA_ARGS__> \
    >::type
  #define JLN_MP_CALL_TRACE_0_ARG(...) \
    typename ::jln::mp::detail::memoizer_impl<__VA_ARGS__, ::jln::mp::list<>>::type
#endif
