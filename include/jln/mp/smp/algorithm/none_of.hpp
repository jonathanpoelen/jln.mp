// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/smp/list/is_list.hpp>
#include <jln/mp/algorithm/none_of.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class C>
  struct smp_none_of;

  template<class Pred, class C>
  struct smp_all_of;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using none_of = typename detail::smp_none_of<Pred, C>::type;

  template<class Pred, class C = identity>
  using all_of = typename detail::smp_all_of<Pred, C>::type;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, none_of<Pred, C>>
  {
    using type = smp::none_of<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of<Pred, C>>
  {
    using type = smp::all_of<sfinae<Pred>, sfinae<C>>;
  };


  template<class Pred, class C>
  struct smp_none_of
  {
    using type = smp::drop_until<Pred,
      smp::always<false_, assume_positive_number_barrier<C>>,
      smp::always<true_, assume_positive_number_barrier<C>>
    >;
  };

  template<class T, class C>
  struct smp_none_of<is<T>, C>
  {
    using type = contract<none_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_none_of<is<T, not_<>>, C>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_none_of<try_contract<is<T>>, C>
  {
    using type = contract<none_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_none_of<try_contract<is<T, not_<>>>, C>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };


  template<class Pred, class C>
  struct smp_all_of
  {
    using type = smp::drop_while<Pred,
      smp::always<false_, assume_positive_number_barrier<C>>,
      smp::always<true_, assume_positive_number_barrier<C>>
    >;
  };

  template<class T, class C>
  struct smp_all_of<is<T>, C>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_all_of<is<T, not_<>>, C>
  {
    using type = contract<none_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_all_of<try_contract<is<T>>, C>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class T, class C>
  struct smp_all_of<try_contract<is<T, not_<>>>, C>
  {
    using type = contract<none_of<is<T>, assume_positive_number_barrier<C>>>;
  };

#if !JLN_MP_GCC
  template<class C>
  struct smp_all_of<is_list<>, C>
  {
    using type = contract<all_of<is_list<>, assume_positive_number_barrier<C>>>;
  };

  template<class C>
  struct smp_all_of<try_contract<is_list<>>, C>
  {
    using type = contract<all_of<is_list<>, assume_positive_number_barrier<C>>>;
  };
#endif
}
/// \endcond

