// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/list/at.hpp>
#include <jln/mp/smp/utility/always.hpp>
#include <jln/mp/smp/number/to_bool.hpp>
#include <jln/mp/functional/invoke_twice.hpp>
#include <jln/mp/functional/if.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class TC, class FC>
  struct smp_if_select;
}
/// \endcond

namespace jln::mp::smp
{
  template<class Pred, class TC, class FC = always<false_>>
  using if_ = typename detail::smp_if_select<subcontract<TC>, subcontract<FC>>
    ::template f<Pred>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, if_<Pred, TC, FC>>
  {
    using type = smp::if_<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };


  template<class TC, class FC>
  struct smp_if_select
  {
    template<class Pred>
    using f = contract<
      invoke_twice<
        try_<
          subcontract<Pred>,
          try_<
            to_bool<>,
            if_<identity, always<TC>, always<FC>>,
            always<violation>
          >,
          always<violation>
        >
      >
    >;
  };

  template<class True, class False>
  struct smp_if_select<always<True>, always<False>>
  {
    template<class Pred>
    using f = contract<
      try_<
        subcontract<Pred>,
        try_<
          to_bool<>,
          if_<identity, always<True>, always<False>>
        >
      >
    >;
  };

  // select / reverse_select

  template<int_ min_index, class Pred, class TC, class FC>
  using smp_select_impl = test_contract<
    size<greater_than_c<min_index>>,
    invoke_twice<
      try_<
        Pred,
        try_<
          to_bool<>,
          if_<identity, always<TC>, always<FC>>,
          always<violation>
        >,
        always<violation>
      >
    >
  >;

  template<class TC, class FC>
  struct smp_if_select<try_<front<TC>>, try_<front<FC>>>
  {
    template<class Pred>
    using f = smp_select_impl<0, assume_unary_or_more<Pred>, front<TC>, front<FC>>;
  };

  template<bool>
  struct smp_select_pred_unary_or_binary
  {
    template<class Pred>
    using f = assume_unary_or_more<Pred>;
  };

  template<>
  struct smp_select_pred_unary_or_binary<false>
  {
    template<class Pred>
    using f = assume_binary_or_more<Pred>;
  };

  template<class TC, class FC, int_ min_index, unsigned ndrop>
  struct smp_if_select<
    try_<front<TC>>,
    if_<size<greater_than_c<min_index>>, drop_front_c<ndrop, front<FC>>, violation>
  >
  {
    template<class Pred>
    using f = typename conditional_c<min_index < ndrop>::template f<
      bad_contract,
      smp_select_impl<
        min_index,
        typename smp_select_pred_unary_or_binary<min_index == 0>::template f<Pred>,
        front<TC>,
        drop_front_c<ndrop, front<FC>>
      >
    >;
  };


  template<class TC, class FC, int_ min_index, unsigned ndrop>
  struct smp_if_select<
    if_<size<greater_than_c<min_index>>, drop_front_c<ndrop, front<TC>>, violation>,
    try_<front<FC>>
  >
  {
    template<class Pred>
    using f = typename conditional_c<min_index < ndrop>::template f<
      bad_contract,
      smp_select_impl<
        min_index,
        typename smp_select_pred_unary_or_binary<min_index == 0>::template f<Pred>,
        drop_front_c<ndrop, front<TC>>,
        front<FC>
      >
    >;
  };

  template<class TC, class FC, int_ min_indexT, int_ min_indexF, unsigned ndropT, unsigned ndropF>
  struct smp_if_select<
    if_<size<greater_than_c<min_indexT>>, drop_front_c<ndropT, front<TC>>, violation>,
    if_<size<greater_than_c<min_indexF>>, drop_front_c<ndropF, front<FC>>, violation>
  >
  {
    template<class Pred, int_ max_index = min_indexT < min_indexF ? min_indexF : min_indexT>
    using f = typename conditional_c<max_index < ndropT || max_index < ndropF>::template f<
      bad_contract,
      smp_select_impl<
        max_index,
        typename smp_select_pred_unary_or_binary<max_index == 0>::template f<Pred>,
        drop_front_c<ndropT, try_<TC>>,
        drop_front_c<ndropF, front<FC>>
      >
    >;
  };
}
/// \endcond
