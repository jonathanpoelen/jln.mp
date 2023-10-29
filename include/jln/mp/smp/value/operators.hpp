// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/value/operators.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/smp/list/size.hpp>
#include <jln/mp/smp/list/push_back.hpp>
#include <jln/mp/smp/list/pop_front.hpp>
#include <jln/mp/smp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class C, int i = 0>
  using smp_opv_default = contract<
    if_<
      size<>,
      try_<Tpl<assume_unary<C>>>,
      always<val<i>, assume_unary<C>>
    >
  >;

// x/0 is not a substitution failure
#if JLN_MP_MSVC || JLN_MP_CUDA
  template<template<class...> class Tpl, class C, int i = 0>
  using smp_opv_without_zero = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<Tpl<assume_unary<C>>>,
        violation
      >,
      always<val<i>, assume_unary<C>>
    >
  >;

  template<class C>
  using smp_opv_without_zero_and_with_value = contract<
    if_<
      size<>,
      if_<
        pop_front<and_<>>,
        try_<C>,
        violation
      >,
      violation
    >
  >;
# define JLN_smp_opv_without_zero detail::smp_opv_without_zero
# define JLN_smp_opv_without_zero_and_with_value detail::smp_opv_without_zero_and_with_value
#else
# define JLN_smp_opv_without_zero detail::smp_opv_default
# define JLN_smp_opv_without_zero_and_with_value try_contract
#endif
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using val_or = try_contract<mp::val_or<assume_unary<C>>>;

  template<class C = identity>
  using val_and = try_contract<mp::val_and<assume_unary<C>>>;

  template<class C = identity>
  using val_left_or = try_contract<mp::val_left_or<assume_unary<C>>>;

  template<class C = identity>
  using val_left_and = try_contract<mp::val_left_and<assume_unary<C>>>;

  template<class C = identity>
  using val_add = try_contract<mp::val_add<assume_unary<C>>>;

  template<class C = identity>
  using val_add0 = detail::smp_opv_default<mp::val_add, C>;

  template<class C = identity>
  using val_left_add = try_contract<mp::val_left_add<assume_unary<C>>>;

  template<class C = identity>
  using val_left_add0 = detail::smp_opv_default<mp::val_left_add, C>;

  template<class C = identity>
  using val_sub = try_contract<mp::val_sub<assume_unary<C>>>;

  template<class C = identity>
  using val_sub0 = detail::smp_opv_default<mp::val_sub, C>;

  template<class C = identity>
  using val_lshift = try_contract<mp::val_lshift<assume_unary<C>>>;

  template<class C = identity>
  using val_lshift0 = detail::smp_opv_default<mp::val_lshift, C>;

  template<class C = identity>
  using val_rshift = try_contract<mp::val_rshift<assume_unary<C>>>;

  template<class C = identity>
  using val_rshift0 = detail::smp_opv_default<mp::val_rshift, C>;

  template<class C = identity>
  using val_mul = try_contract<mp::val_mul<assume_unary<C>>>;

  template<class C = identity>
  using val_mul0 = detail::smp_opv_default<mp::val_mul, C>;

  template<class C = identity>
  using val_mul1 = detail::smp_opv_default<mp::val_mul, C, 1>;

  template<class C = identity>
  using val_left_mul = try_contract<mp::val_left_mul<assume_unary<C>>>;

  template<class C = identity>
  using val_left_mul0 = detail::smp_opv_default<mp::val_left_mul, C>;

  template<class C = identity>
  using val_left_mul1 = detail::smp_opv_default<mp::val_left_mul, C, 1>;

  template<class C = identity>
  using val_div = JLN_smp_opv_without_zero_and_with_value<mp::val_div<assume_unary<C>>>;

  template<class C = identity>
  using val_div0 = JLN_smp_opv_without_zero<mp::val_div, C>;

  template<class C = identity>
  using val_div1 = JLN_smp_opv_without_zero<mp::val_div, C, 1>;

  template<class C = identity>
  using val_mod = JLN_smp_opv_without_zero_and_with_value<mp::val_mod<assume_unary<C>>>;

  template<class C = identity>
  using val_mod0 = JLN_smp_opv_without_zero<mp::val_mod, C>;

  template<class C = identity>
  using val_mod1 = JLN_smp_opv_without_zero<mp::val_mod, C, 1>;

  template<class C = identity>
  using val_xor = try_contract<mp::val_xor<assume_unary<C>>>;

  template<class C = identity>
  using val_xor0 = detail::smp_opv_default<mp::val_xor, C>;

  template<class C = identity>
  using val_left_xor = try_contract<mp::val_left_xor<assume_unary<C>>>;

  template<class C = identity>
  using val_left_xor0 = detail::smp_opv_default<mp::val_left_xor, C>;

  template<class C = identity>
  using val_bit_and = try_contract<mp::val_bit_and<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_and0 = detail::smp_opv_default<mp::val_bit_and, C>;

  template<class C = identity>
  using val_left_bit_and = try_contract<mp::val_left_bit_and<assume_unary<C>>>;

  template<class C = identity>
  using val_left_bit_and0 = detail::smp_opv_default<mp::val_left_bit_and, C>;

  template<class C = identity>
  using val_bit_or = try_contract<mp::val_bit_or<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_or0 = detail::smp_opv_default<mp::val_bit_or, C>;

  template<class C = identity>
  using val_left_bit_or = try_contract<mp::val_left_bit_or<assume_unary<C>>>;

  template<class C = identity>
  using val_left_bit_or0 = detail::smp_opv_default<mp::val_left_bit_or, C>;

  template<class C = identity>
  using val_neg = try_contract<mp::val_neg<assume_unary<C>>>;

  template<class C = identity>
  using val_unary_plus = try_contract<mp::val_unary_plus<assume_unary<C>>>;

  template<class C = identity>
  using val_not = try_contract<mp::val_not<assume_unary<C>>>;

  template<class C = identity>
  using val_bit_not = try_contract<mp::val_bit_not<assume_unary<C>>>;

  template<class C = identity>
  using val_inc = try_contract<mp::val_inc<assume_unary<C>>>;

  template<class C = identity>
  using val_dec = try_contract<mp::val_dec<assume_unary<C>>>;

  template<class C = identity>
  using val_equal = try_contract<mp::val_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_not_equal = try_contract<mp::val_not_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_less = try_contract<mp::val_less<assume_unary<C>>>;

  template<class C = identity>
  using val_less_equal = try_contract<mp::val_less_equal<assume_unary<C>>>;

  template<class C = identity>
  using val_greater = try_contract<mp::val_greater<assume_unary<C>>>;

  template<class C = identity>
  using val_greater_equal = try_contract<mp::val_greater_equal<assume_unary<C>>>;

  template<class x, class C = identity>
  using val_equal_to = contract<
    mp::push_back<x,
      mp::try_<mp::val_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_not_equal_to = contract<
    mp::push_back<x,
      mp::try_<mp::val_not_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_less_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_less<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_less_equal_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_less_equal<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_greater_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_greater<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using val_greater_equal_than = contract<
    mp::push_back<x,
      mp::try_<mp::val_greater_equal<assume_unary<C>>>>>;

  template<auto x, class C = identity>
  using val_equal_to_c = val_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_not_equal_to_c = val_not_equal_to<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_than_c = val_less_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_less_equal_than_c = val_less_equal_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_than_c = val_greater_than<val<x>, C>;

  template<auto x, class C = identity>
  using val_greater_equal_than_c = val_greater_equal_than<val<x>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_or<C>>
  {
    using type = smp::val_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_and<C>>
  {
    using type = smp::val_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_or<C>>
  {
    using type = smp::val_left_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_and<C>>
  {
    using type = smp::val_left_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_add<C>>
  {
    using type = smp::val_add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_add<C>>
  {
    using type = smp::val_left_add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_sub<C>>
  {
    using type = smp::val_sub<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_lshift<C>>
  {
    using type = smp::val_lshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_rshift<C>>
  {
    using type = smp::val_rshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_mul<C>>
  {
    using type = smp::val_mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_mul<C>>
  {
    using type = smp::val_left_mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_div<C>>
  {
    using type = smp::val_div<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_mod<C>>
  {
    using type = smp::val_mod<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_xor<C>>
  {
    using type = smp::val_xor<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_xor<C>>
  {
    using type = smp::val_left_xor<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_and<C>>
  {
    using type = smp::val_bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_bit_and<C>>
  {
    using type = smp::val_left_bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_or<C>>
  {
    using type = smp::val_bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_left_bit_or<C>>
  {
    using type = smp::val_left_bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_neg<C>>
  {
    using type = smp::val_neg<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_unary_plus<C>>
  {
    using type = smp::val_unary_plus<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_not<C>>
  {
    using type = smp::val_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_bit_not<C>>
  {
    using type = smp::val_bit_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_inc<C>>
  {
    using type = smp::val_inc<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_dec<C>>
  {
    using type = smp::val_dec<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_equal<C>>
  {
    using type = smp::val_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_not_equal<C>>
  {
    using type = smp::val_not_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_less<C>>
  {
    using type = smp::val_less<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_less_equal<C>>
  {
    using type = smp::val_less_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_greater<C>>
  {
    using type = smp::val_greater<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, val_greater_equal<C>>
  {
    using type = smp::val_greater_equal<sfinae<C>>;
  };
}

#undef JLN_smp_opv_without_zero
#undef JLN_smp_opv_without_zero_and_with_value
/// \endcond
