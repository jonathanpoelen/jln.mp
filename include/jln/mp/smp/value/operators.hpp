#pragma once

#include "../../value/operators.hpp"
#include "../functional/identity.hpp"
#include "../functional/if.hpp"
#include "../list/size.hpp"
#include "../list/push_back.hpp"

/// \cond
namespace jln::mp::detail
{
  template<template<class...> class Tpl, class C, int i = 0>
  using smp_opv_default = contract<
    if_<
      size<>,
      try_invoke<Tpl<assume_unary<C>>>,
      always<val<i>, assume_unary<C>>>>;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = identity>
  using or_v = try_contract<mp::or_v<assume_unary<C>>>;

  template<class C = identity>
  using and_v = try_contract<mp::and_v<assume_unary<C>>>;

  template<class C = identity>
  using add_v = try_contract<mp::add_v<assume_unary<C>>>;

  template<class C = identity>
  using add0_v = detail::smp_opv_default<mp::add_v, C>;

  template<class C = identity>
  using sub_v = try_contract<mp::sub_v<assume_unary<C>>>;

  template<class C = identity>
  using sub0_v = detail::smp_opv_default<mp::sub_v, C>;

  template<class C = identity>
  using lshift_v = try_contract<mp::lshift_v<assume_unary<C>>>;

  template<class C = identity>
  using lshift0_v = detail::smp_opv_default<mp::lshift_v, C>;

  template<class C = identity>
  using rshift_v = try_contract<mp::rshift_v<assume_unary<C>>>;

  template<class C = identity>
  using rshift0_v = detail::smp_opv_default<mp::rshift_v, C>;

  template<class C = identity>
  using mul_v = try_contract<mp::mul_v<assume_unary<C>>>;

  template<class C = identity>
  using mul0_v = detail::smp_opv_default<mp::mul_v, C>;

  template<class C = identity>
  using mul1_v = detail::smp_opv_default<mp::mul_v, C, 1>;

  template<class C = identity>
  using div_v = try_contract<mp::div_v<assume_unary<C>>>;

  template<class C = identity>
  using div0_v = detail::smp_opv_default<mp::div_v, C>;

  template<class C = identity>
  using div1_v = detail::smp_opv_default<mp::div_v, C, 1>;

  template<class C = identity>
  using mod_v = try_contract<mp::mod_v<assume_unary<C>>>;

  template<class C = identity>
  using mod0_v = detail::smp_opv_default<mp::mod_v, C>;

  template<class C = identity>
  using mod1_v = detail::smp_opv_default<mp::mod_v, C, 1>;

  template<class C = identity>
  using xor_v = try_contract<mp::xor_v<assume_unary<C>>>;

  template<class C = identity>
  using xor0_v = detail::smp_opv_default<mp::xor_v, C>;

  template<class C = identity>
  using bit_and_v = try_contract<mp::bit_and_v<assume_unary<C>>>;

  template<class C = identity>
  using bit_and0_v = detail::smp_opv_default<mp::bit_and_v, C>;

  template<class C = identity>
  using bit_or_v = try_contract<mp::bit_or_v<assume_unary<C>>>;

  template<class C = identity>
  using bit_or0_v = detail::smp_opv_default<mp::bit_or_v, C>;

  template<class C = identity>
  using neg_v = try_contract<mp::neg_v<assume_unary<C>>>;

  template<class C = identity>
  using unary_plus_v = try_contract<mp::unary_plus_v<assume_unary<C>>>;

  template<class C = identity>
  using not_v = try_contract<mp::not_v<assume_unary<C>>>;

  template<class C = identity>
  using bit_not_v = try_contract<mp::bit_not_v<assume_unary<C>>>;

  template<class C = identity>
  using inc_v = try_contract<mp::inc_v<assume_unary<C>>>;

  template<class C = identity>
  using dec_v = try_contract<mp::dec_v<assume_unary<C>>>;

  template<class C = identity>
  using equal_v = try_contract<mp::equal_v<assume_unary<C>>>;

  template<class C = identity>
  using not_equal_v = try_contract<mp::not_equal_v<assume_unary<C>>>;

  template<class C = identity>
  using less_v = try_contract<mp::less_v<assume_unary<C>>>;

  template<class C = identity>
  using less_equal_v = try_contract<mp::less_equal_v<assume_unary<C>>>;

  template<class C = identity>
  using greater_v = try_contract<mp::greater_v<assume_unary<C>>>;

  template<class C = identity>
  using greater_equal_v = try_contract<mp::greater_equal_v<assume_unary<C>>>;

  template<class x, class C = identity>
  using equal_to_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::equal_v<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using not_equal_to_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::not_equal_v<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using less_than_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::less_v<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using less_equal_than_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::less_equal_v<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using greater_than_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::greater_v<assume_unary<C>>>>>;

  template<class x, class C = identity>
  using greater_equal_than_v = contract<
    mp::push_back<x,
      mp::try_invoke<mp::greater_equal_v<assume_unary<C>>>>>;

  template<auto x, class C = identity>
  using equal_to_c_v = equal_to_v<val<x>, C>;

  template<auto x, class C = identity>
  using not_equal_to_c_v = not_equal_to_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_than_c_v = less_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using less_equal_than_c_v = less_equal_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_than_c_v = greater_than_v<val<x>, C>;

  template<auto x, class C = identity>
  using greater_equal_than_c_v = greater_equal_than_v<val<x>, C>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, or_v<C>>
  {
    using type = smp::or_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, and_v<C>>
  {
    using type = smp::and_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, add_v<C>>
  {
    using type = smp::add_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, sub_v<C>>
  {
    using type = smp::sub_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, lshift_v<C>>
  {
    using type = smp::lshift_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, rshift_v<C>>
  {
    using type = smp::rshift_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mul_v<C>>
  {
    using type = smp::mul_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, div_v<C>>
  {
    using type = smp::div_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, mod_v<C>>
  {
    using type = smp::mod_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, xor_v<C>>
  {
    using type = smp::xor_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_and_v<C>>
  {
    using type = smp::bit_and_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_or_v<C>>
  {
    using type = smp::bit_or_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, neg_v<C>>
  {
    using type = smp::neg_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unary_plus_v<C>>
  {
    using type = smp::unary_plus_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_v<C>>
  {
    using type = smp::not_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, bit_not_v<C>>
  {
    using type = smp::bit_not_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, inc_v<C>>
  {
    using type = smp::inc_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, dec_v<C>>
  {
    using type = smp::dec_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, equal_v<C>>
  {
    using type = smp::equal_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, not_equal_v<C>>
  {
    using type = smp::not_equal_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less_v<C>>
  {
    using type = smp::less_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, less_equal_v<C>>
  {
    using type = smp::less_equal_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater_v<C>>
  {
    using type = smp::greater_v<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, greater_equal_v<C>>
  {
    using type = smp::greater_equal_v<sfinae<C>>;
  };
}
/// \endcond
