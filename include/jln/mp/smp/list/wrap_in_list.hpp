// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/concepts.hpp>
#include <jln/mp/smp/algorithm/same.hpp>
#include <jln/mp/smp/utility/is_not.hpp>
#include <jln/mp/smp/functional/tee.hpp>
#include <jln/mp/smp/functional/continuation.hpp>
#include <jln/mp/functional/try.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

namespace jln::mp::smp
{
  template<class Pred>
  using wrap_in_list_if = try_contract<mp::wrap_in_list_if<
    concepts::predicate_or_else<assume_unary_or_more<Pred>, mp::violation>>>;

  template<class Pred>
  using wrap_in_list_if_not = try_contract<mp::wrap_in_list_if_not<
    concepts::predicate_or_else<assume_unary_or_more<Pred>, mp::violation>>>;

  template<bool b>
  using wrap_in_list_c = contract<mp::wrap_in_list_c<b>>;
}

JLN_MP_MAKE_REGULAR_SMP1_P(wrap_in_list, (N), smp::wrap_in_list_c<N::value>)

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if<Pred>>
  {
    using type = smp::wrap_in_list_if<sfinae<Pred>>;
  };

  template<template<class> class sfinae, class Pred>
  struct _sfinae<sfinae, _wrap_in_list_if_not<Pred>>
  {
    using type = smp::wrap_in_list_if_not<sfinae<Pred>>;
  };

  template<template<class> class sfinae, bool b>
  struct _sfinae<sfinae, wrap_in_list_c<b>>
  {
    using type = smp::wrap_in_list_c<b>;
  };
}
/// \endcond
