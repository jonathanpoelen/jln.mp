#pragma once

#include "../assume.hpp"
#include "../../number/operators.hpp"
#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../list/size.hpp"
#include "../list/push_back.hpp"

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class C, int_ i = 0>
  using smp_op_default = contract<
    if_<
      size<>,
      try_<Tpl<assume_number<C>>>,
      always<number<i>, assume_number<C>>>>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using or_ = try_contract<mp::or_<assume_number<C>>>;

  template<class C = identity>
  using and_ = try_contract<mp::and_<assume_number<C>>>;

  template<class C = identity>
  using add = try_contract<mp::add<assume_number<C>>>;

  template<class C = identity>
  using add0 = detail::smp_op_default<mp::add, C>;

  template<class C = identity>
  using sub = try_contract<mp::sub<assume_number<C>>>;

  template<class C = identity>
  using sub0 = detail::smp_op_default<mp::sub, C>;

  template<class C = identity>
  using lshift = try_contract<mp::lshift<assume_number<C>>>;

  template<class C = identity>
  using lshift0 = detail::smp_op_default<mp::lshift, C>;

  template<class C = identity>
  using rshift = try_contract<mp::rshift<assume_number<C>>>;

  template<class C = identity>
  using rshift0 = detail::smp_op_default<mp::rshift, C>;

  template<class C = identity>
  using mul = try_contract<mp::mul<assume_number<C>>>;

  template<class C = identity>
  using mul0 = detail::smp_op_default<mp::mul, C>;

  template<class C = identity>
  using mul1 = detail::smp_op_default<mp::mul, C, 1>;

  template<class C = identity>
  using div = try_contract<mp::div<assume_number<C>>>;

  template<class C = identity>
  using div0 = detail::smp_op_default<mp::div, C>;

  template<class C = identity>
  using div1 = detail::smp_op_default<mp::div, C, 1>;

  template<class C = identity>
  using mod = try_contract<mp::mod<assume_number<C>>>;

  template<class C = identity>
  using mod0 = detail::smp_op_default<mp::mod, C>;

  template<class C = identity>
  using mod1 = detail::smp_op_default<mp::mod, C, 1>;

  template<class C = identity>
  using xor_ = try_contract<mp::xor_<assume_number<C>>>;

  template<class C = identity>
  using xor0 = detail::smp_op_default<mp::xor_, C>;

  template<class C = identity>
  using bit_and = try_contract<mp::bit_and<assume_number<C>>>;

  template<class C = identity>
  using bit_and0 = detail::smp_op_default<mp::bit_and, C>;

  template<class C = identity>
  using bit_or = try_contract<mp::bit_or<assume_number<C>>>;

  template<class C = identity>
  using bit_or0 = detail::smp_op_default<mp::bit_or, C>;

  template<class C = identity>
  using neg = try_contract<mp::neg<assume_number<C>>>;

  template<class C = identity>
  using unary_plus = try_contract<mp::unary_plus<assume_number<C>>>;

  template<class C = identity>
  using not_ = try_contract<mp::not_<assume_number<C>>>;

  template<class C = identity>
  using bit_not = try_contract<mp::bit_not<assume_number<C>>>;

  template<class C = identity>
  using inc = try_contract<mp::inc<assume_number<C>>>;

  template<class C = identity>
  using dec = try_contract<mp::dec<assume_number<C>>>;

  template<class C = identity>
  using equal = try_contract<mp::equal<assume_number<C>>>;

  template<class C = identity>
  using not_equal = try_contract<mp::not_equal<assume_number<C>>>;

  template<class C = identity>
  using less = try_contract<mp::less<assume_number<C>>>;

  template<class C = identity>
  using less_equal = try_contract<mp::less_equal<assume_number<C>>>;

  template<class C = identity>
  using greater = try_contract<mp::greater<assume_number<C>>>;

  template<class C = identity>
  using greater_equal = try_contract<mp::greater_equal<assume_number<C>>>;

  template<class N, class C = identity>
  using equal_to = contract<
    mp::push_back<N,
      mp::try_<mp::equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using not_equal_to = contract<
    mp::push_back<N,
      mp::try_<mp::not_equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using less_than = contract<
    mp::push_back<N,
      mp::try_<mp::less<assume_number<C>>>>>;

  template<class N, class C = identity>
  using less_equal_than = contract<
    mp::push_back<N,
      mp::try_<mp::less_equal<assume_number<C>>>>>;

  template<class N, class C = identity>
  using greater_than = contract<
    mp::push_back<N,
      mp::try_<mp::greater<assume_number<C>>>>>;

  template<class N, class C = identity>
  using greater_equal_than = contract<
    mp::push_back<N,
      mp::try_<mp::greater_equal<assume_number<C>>>>>;

  template<int_ n, class C = identity>
  using equal_to_c = equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using not_equal_to_c = not_equal_to<number<n>, C>;

  template<int_ n, class C = identity>
  using less_than_c = less_than<number<n>, C>;

  template<int_ n, class C = identity>
  using less_equal_than_c = less_equal_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_than_c = greater_than<number<n>, C>;

  template<int_ n, class C = identity>
  using greater_equal_than_c = greater_equal_than<number<n>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, or_<C>>
  {
    using type = smp::or_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, and_<C>>
  {
    using type = smp::and_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, add<C>>
  {
    using type = smp::add<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sub<C>>
  {
    using type = smp::sub<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, lshift<C>>
  {
    using type = smp::lshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rshift<C>>
  {
    using type = smp::rshift<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mul<C>>
  {
    using type = smp::mul<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, div<C>>
  {
    using type = smp::div<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mod<C>>
  {
    using type = smp::mod<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, xor_<C>>
  {
    using type = smp::xor_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_and<C>>
  {
    using type = smp::bit_and<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_or<C>>
  {
    using type = smp::bit_or<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, neg<C>>
  {
    using type = smp::neg<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unary_plus<C>>
  {
    using type = smp::unary_plus<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_<C>>
  {
    using type = smp::not_<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_not<C>>
  {
    using type = smp::bit_not<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, inc<C>>
  {
    using type = smp::inc<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, dec<C>>
  {
    using type = smp::dec<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, equal<C>>
  {
    using type = smp::equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_equal<C>>
  {
    using type = smp::not_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less<C>>
  {
    using type = smp::less<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less_equal<C>>
  {
    using type = smp::less_equal<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater<C>>
  {
    using type = smp::greater<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater_equal<C>>
  {
    using type = smp::greater_equal<sfinae<C>>;
  };


  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, or_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::numbers, and_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, not_);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, inc);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, dec);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, neg);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, unary_plus);
  JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::number, bit_not);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, not_equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, less);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, less_equal);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, greater);
  // JLN_MP_MAKE_EXPECTED_ARGUMENT1(argument_category::binary_number, greater_equal);
}
/// \endcond
