// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/assume.hpp>
#include <jln/mp/algorithm/remove_unique.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Cmp>
  struct smp_mk_remove_unique;

  template<class Cmp>
  struct smp_mk_copy_unique;
}
/// \endcond

namespace jln::mp::smp
{
  template<class C = listify>
  using remove_unique = contract<mp::remove_unique<subcontract<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using remove_unique_if = typename detail::smp_mk_remove_unique<Cmp>::template f<C>;

  template<class C = listify>
  using copy_unique = contract<mp::copy_unique<subcontract<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = listify>
  using copy_unique_if = typename detail::smp_mk_copy_unique<Cmp>::template f<C>;
}


#include <jln/mp/smp/algorithm/any_of.hpp>

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, remove_unique<C>>
  {
    using type = smp::remove_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, detail::_remove_unique_if<Cmp, C>>
  {
    using type = smp::remove_unique_if<sfinae<Cmp>, sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, copy_unique<C>>
  {
    using type = smp::copy_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, detail::_copy_unique_if<Cmp, C>>
  {
    using type = smp::copy_unique_if<sfinae<Cmp>, sfinae<C>>;
  };


  template<class, int_... ints>
  struct smp_remove_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<smp::any_of<
          contract<push_back<xs, Cmp>>,
          contract<lift<wrap_in_list>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct smp_remove_unique_if_impl<int_>
  : remove_unique_if_impl<int_>
  {};

  template<int_ i>
  struct smp_remove_unique_if_impl<int_, i>
  : remove_unique_if_impl<int_>
  {};

  template<class Cmp, class C>
  struct smp_remove_unique_if
  {
    template<class... xs>
    using f = typename try_<
      JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), smp_remove_unique_if_impl)
    >::template f<C, Cmp, xs...>;
  };

  template<class Cmp>
  struct smp_mk_remove_unique
  {
    template<class C>
    using f = contract<smp_remove_unique_if<assume_binary<Cmp>, subcontract<C>>>;
  };

  template<>
  struct smp_mk_remove_unique<contract<lift<std::is_same>>>
  {
    template<class C>
    using f = smp::remove_unique<C>;
  };


  template<class, int_... ints>
  struct smp_copy_unique_if_impl
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL((
        rotate_c<ints, pop_front<smp::none_of<
          contract<push_back<xs, Cmp>>,
          contract<lift<wrap_in_list>>
        >>>
        ::template f<xs...>
      ), xs)...
    >;
  };

  template<>
  struct smp_copy_unique_if_impl<int_>
  : remove_unique_if_impl<int_>
  {};

  template<int_ i>
  struct smp_copy_unique_if_impl<int_, i>
  : copy_unique_if_impl<int_, i>
  {};

  template<class Cmp, class C>
  struct smp_copy_unique_if
  {
    template<class... xs>
    using f = typename try_<
      JLN_MP_MAKE_INTEGER_SEQUENCE(sizeof...(xs), smp_copy_unique_if_impl)
    >::template f<C, Cmp, xs...>;
  };

  template<class Cmp>
  struct smp_mk_copy_unique
  {
    template<class C>
    using f = contract<smp_copy_unique_if<assume_binary<Cmp>, subcontract<C>>>;
  };

  template<>
  struct smp_mk_copy_unique<contract<lift<std::is_same>>>
  {
    template<class C>
    using f = smp::copy_unique<C>;
  };
}
/// \endcond
