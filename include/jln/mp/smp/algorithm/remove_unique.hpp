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


#include <jln/mp/smp/algorithm/index.hpp>

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


  template<class Indexes>
  struct smp_remove_unique_if_impl;

  template<std::size_t... ints>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      typename rotate_c<ints, pop_front<smp::index_if<
        contract<push_back<xs, Cmp>>,
        contract<always<wrap_in_list_c<true>>>,
        contract<always<wrap_in_list_c<false>>>
      >>>
      ::template f<xs...>
      ::template f<xs>...
    >;
  };

  template<>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct smp_remove_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<class Cmp, class C>
  struct smp_remove_unique_if
  {
    template<class... xs>
    using f = typename try_<
      detail::smp_remove_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
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


  template<class Indexes>
  struct smp_copy_unique_if_impl;

  template<std::size_t... ints>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t, ints...>>
  {
    template<class C, class Cmp, class... xs>
    using f = typename join<C>::template f<
      typename rotate_c<ints, pop_front<smp::index_if<
        contract<push_back<xs, Cmp>>,
        contract<always<wrap_in_list_c<false>>>,
        contract<always<wrap_in_list_c<true>>>
      >>>
      ::template f<xs...>
      ::template f<xs>...
    >;
  };

  template<>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t>>
  : remove_unique_if_impl<std::integer_sequence<std::size_t>>
  {};

  template<std::size_t i>
  struct smp_copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  : copy_unique_if_impl<std::integer_sequence<std::size_t, i>>
  {};

  template<class Cmp, class C>
  struct smp_copy_unique_if
  {
    template<class... xs>
    using f = typename try_<
      detail::smp_copy_unique_if_impl<std::make_index_sequence<sizeof...(xs)>>
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
