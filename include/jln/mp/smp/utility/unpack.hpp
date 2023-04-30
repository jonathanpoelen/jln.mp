#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/utility/unpack.hpp>

namespace jln::mp::smp
{
  template<class C>
  using unpack = try_contract<mp::unpack<subcontract<C>>>;

  template<class C>
  using unpack_append = try_contract<mp::unpack_append<subcontract<C>>>;
}

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/list/front.hpp>

/// \cond
namespace jln::mp::detail
{
  // _unpack<front<C>> is already sfinae compliant, so unpack<try_<front<>>> -> unpack<front<>>
  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<front<C>>>
  {
    using type = smp::unpack<contract<front<assume_unary<sfinae<C>>>>>;
  };


  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack<C>>
  {
    using type = smp::unpack<sfinae<C>>;
  };

  template<template<class> class sfinae, class C>
  struct _sfinae<sfinae, unpack_append<C>>
  {
    using type = smp::unpack_append<sfinae<C>>;
  };


  template<>
  struct optimize_useless_unpack<smp::unpack<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<smp::unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };

  template<>
  struct optimize_useless_unpack<unpack_append<smp::listify>>
  {
    using type = contract<identity>;
  };
}

#include <jln/mp/smp/optimizer/optimizer.hpp>

namespace jln::mp::optimizer
{
  template<class params>
  struct optimized_for_unpack_merge_append_params
  {
    template<class... xs>
    using f = seq<xs..., params>;
  };

  template<class params>
  struct optimized_for_unpack_merge_params
  {
    template<class... xs>
    using f = seq<params, xs...>;
  };

  template<class C, template<class...> class Unpack>
  struct optimized_for_unpack
  {
    template<class... seqs>
    using f = optimized_result<
      typename optimize<C, union_<seqs...>>::output_result,
      Unpack<typename optimize<C, union_<seqs...>>::function>
    >;
  };

  template<template<class...> class UnpackMergeParams>
  struct optimized_for_unpack_extract_params
  {
    template<class param1, class params>
    using f = typename dispatch_unpack<param1>
      ::template f<
        UnpackMergeParams<params>,
        lift<union_>,
        push_front<uncallable, lift<union_>>,
        always<uncallable>>;
  };

  template<class C, class params>
  struct optimizer_impl<unpack<C>, params>
  {
    using type = typename dispatch_split_param_at_1<params>
      ::template f<
        optimized_for_unpack_extract_params<optimized_for_unpack_merge_params>,
        optimized_for_unpack<C, unpack>>;
  };

  template<class C, class params>
  struct optimizer_impl<unpack_append<C>, params>
  {
    using type = typename dispatch_split_param_at_1<params>
      ::template f<
        optimized_for_unpack_extract_params<optimized_for_unpack_merge_append_params>,
        optimized_for_unpack<C, unpack_append>>;
  };
}
/// \endcond
