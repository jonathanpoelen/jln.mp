// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/assume.hpp>
#include <jln/mp/functional/select.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = TC>
  using select = try_contract<
    mp::select<assume_binary_or_more<Pred>, assume_unary<TC>, assume_unary<FC>>
  >;

  template<class Pred, class TC = identity, class FC = TC>
  using reverse_select = try_contract<
    mp::reverse_select<assume_binary_or_more<Pred>, assume_unary<TC>, assume_unary<FC>>
  >;

  template<class Pred, class TC = identity, class FC = TC>
  using select_flip = try_contract<
    mp::select_flip<assume_binary_or_more<Pred>, assume_unary<TC>, assume_unary<FC>>
  >;

  template<class Pred, class TC = identity, class FC = TC>
  using reverse_select_flip = try_contract<
    mp::reverse_select_flip<assume_binary_or_more<Pred>, assume_unary<TC>, assume_unary<FC>>
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, select<Pred, TC, FC>>
  {
    using type = smp::select<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, reverse_select<Pred, TC, FC>>
  {
    using type = smp::reverse_select<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, select_flip<Pred, TC, FC>>
  {
    using type = smp::select_flip<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };

  template<template<class> class sfinae, class Pred, class TC, class FC>
  struct _sfinae<sfinae, reverse_select_flip<Pred, TC, FC>>
  {
    using type = smp::reverse_select_flip<sfinae<Pred>, sfinae<TC>, sfinae<FC>>;
  };
}
/// \endcond
