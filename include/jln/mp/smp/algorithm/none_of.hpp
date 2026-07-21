// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/sfinae_truthy_falsy.hpp>
#include <jln/mp/smp/algorithm/drop_until.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/smp/number/not.hpp>
#include <jln/mp/smp/list/is_list.hpp>
#include <jln/mp/algorithm/none_of.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class Pred, class C,
    class AssumedPred = assume_unary<Pred>,
    class AssumedC = assume_positive_number_barrier<C>>
  struct smp_none_of;

  template<class Pred, class C,
    class AssumedPred = assume_unary<Pred>,
    class AssumedC = assume_positive_number_barrier<C>>
  struct smp_all_of;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class C = identity>
  using none_of = typename detail::smp_none_of<Pred, C>::type;

  template<class Pred, class C = identity>
  using all_of = typename detail::smp_all_of<Pred, C>::type;

  template<class Pred, class C = identity>
  using any_of = none_of<Pred, not_<C>>;

#if JLN_MP_FEATURE_CONCEPTS
  template<class Pred, class C = identity>
  using any_of_sfinae_truthy = contract<
    mp::any_of_sfinae_truthy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using any_of_sfinae_falsy = contract<
    mp::any_of_sfinae_falsy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using all_of_sfinae_truthy = contract<
    mp::all_of_sfinae_truthy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using all_of_sfinae_falsy = contract<
    mp::all_of_sfinae_falsy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using none_of_sfinae_truthy = contract<
    mp::none_of_sfinae_truthy<assume_unary<Pred>, assume_number<C>>
  >;

  template<class Pred, class C = identity>
  using none_of_sfinae_falsy = contract<
    mp::none_of_sfinae_falsy<assume_unary<Pred>, assume_number<C>>
  >;
#endif
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


  template<class Pred, class C, class AssumedPred, class AssumedC>
  struct smp_none_of
  {
    using type = smp::drop_until<Pred,
      smp::always<false_, AssumedC>,
      smp::always<true_, AssumedC>
    >;
  };

  template<class Pred, class C, class T, class AssumedC>
  struct smp_none_of<Pred, C, is<T>, AssumedC>
  {
    using type = contract<none_of<is<T>, AssumedC>>;
  };

  template<class Pred, class C, class T, class AssumedC>
  struct smp_none_of<Pred, C, is<T, not_<>>, AssumedC>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };


  template<class Pred, class C, class AssumedPred, class AssumedC>
  struct smp_all_of
  {
    using type = smp::drop_while<Pred,
      smp::always<false_, AssumedC>,
      smp::always<true_, AssumedC>
    >;
  };

  template<class Pred, class C, class T, class AssumedC>
  struct smp_all_of<Pred, C, is<T>, AssumedC>
  {
    using type = contract<all_of<is<T>, assume_positive_number_barrier<C>>>;
  };

  template<class Pred, class C, class T, class AssumedC>
  struct smp_all_of<Pred, C, is<T, not_<>>, AssumedC>
  {
    using type = contract<none_of<is<T>, assume_positive_number_barrier<C>>>;
  };

#if !JLN_MP_GCC
  template<class Pred, class C, class AssumedC>
  struct smp_all_of<Pred, C, is_list<>, AssumedC>
  {
    using type = contract<all_of<is_list<>, assume_positive_number_barrier<C>>>;
  };
#endif

#if JLN_MP_FEATURE_CONCEPTS
  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, any_of_sfinae_truthy<Pred, C>>
  {
    using type = smp::any_of_sfinae_truthy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, any_of_sfinae_falsy<Pred, C>>
  {
    using type = smp::any_of_sfinae_falsy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of_sfinae_truthy<Pred, C>>
  {
    using type = smp::all_of_sfinae_truthy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, all_of_sfinae_falsy<Pred, C>>
  {
    using type = smp::all_of_sfinae_falsy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, none_of_sfinae_truthy<Pred, C>>
  {
    using type = smp::none_of_sfinae_truthy<sfinae<Pred>, sfinae<C>>;
  };

  template<template<class> class sfinae, class Pred, class C>
  struct _sfinae<sfinae, none_of_sfinae_falsy<Pred, C>>
  {
    using type = smp::none_of_sfinae_falsy<sfinae<Pred>, sfinae<C>>;
  };
#endif
}
/// \endcond

