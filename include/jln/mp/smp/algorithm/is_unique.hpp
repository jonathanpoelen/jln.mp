#pragma once

#include <jln/mp/smp/algorithm/unique.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/algorithm/is_unique.hpp>


namespace jln::mp::smp
{
  template<class C = identity>
  using is_unique = contract<mp::is_unique<assume_positive_number<C>>>;

  template<class Cmp = contract<mp::lift<std::is_same>>, class C = identity>
  using is_unique_if = detail::sfinae<mp::is_unique_if<
    assume_binary_barrier<Cmp>, assume_positive_number_barrier<C>>>;
}


/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, is_unique_impl<C>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    is_unique_unpack<is_unique_set_cmp_push_back_or_void<
      JLN_MP_TRACE_F(contract<mp::lift<std::is_same>>)
    >>, C
  >>>
  {
    using type = smp::is_unique<sfinae<C>>;
  };

  template<class Cmp>
  struct smp_is_unique_set_cmp_push_back_or_void
  {
    template<class x, class... xs>
    using f = typename conditional_c<
      smp::none_of<contract<push_back<x, Cmp>>>
      ::template f<xs...>::value
    >::template f<list<xs..., x>, void>;
  };

  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, push_front<list<>, fold_left<
    is_unique_unpack<is_unique_set_cmp_push_back_or_void<JLN_MP_TRACE_F(Cmp)>>,
    is_not<void, C>
  >>>
  {
    using type = contract<push_front<list<>, smp::fold_left<
      contract<is_unique_unpack<try_<smp_is_unique_set_cmp_push_back_or_void<
        JLN_MP_TRACE_F(assume_binary<sfinae<Cmp>>)
      >>>>,
      contract<is_not<void, assume_unary<sfinae<C>>>>
    >>>;
  };
}
/// \endcond
