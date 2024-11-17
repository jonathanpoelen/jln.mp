// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/number/number.hpp>

// fix narrowing based on type:
//
// template<int>
// struct X {};
//
// template<class... T>
// struct A : X<int{sizeof...(T)}> // narrowing error with msvc 19.38
// {};

#if JLN_MP_WORKAROUND(JLN_MP_MSVC, < 1942)
namespace jln::mp::detail
{
  template<bool is_neg>
  struct integral_as_impl;

  struct integral_conversion_error
  {};

  template<>
  struct integral_as_impl<true>
  {
    template<long long n>
    using as_bool = integral_conversion_error;

    template<long long n>
    struct as_int_t : number<n>
    {};

    template<long long n>
    using as_uint_t = integral_conversion_error;
  };

  template<>
  struct integral_as_impl<false>
  {
    template<unsigned long long n, bool = n <= 1>
    struct as_bool : number<n>
    {};

    template<unsigned long long n>
    struct as_bool<n, false>
    {};


    template<unsigned long long n, bool = n <= (~0ull >> 1)>
    struct as_int_t : number<n>
    {};

    template<unsigned long long n>
    struct as_int_t<n, false>
    {};


    template<unsigned long long n>
    struct as_uint_t : number<n>
    {};
  };
}
#  define JLN_MP_INTEGRAL_AS(T, ...) \
  ::jln::mp::detail::integral_as_impl<__VA_ARGS__ < 0>::template as_##T<__VA_ARGS__>::value
#else
#  define JLN_MP_INTEGRAL_AS(T, ...) T{__VA_ARGS__}
#endif
