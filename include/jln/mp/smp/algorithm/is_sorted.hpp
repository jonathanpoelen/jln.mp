// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/drop_until_xs.hpp>
#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/number/as_bool.hpp>
#include <jln/mp/smp/number/operators.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/utility/always.hpp>
#include <jln/mp/algorithm/is_sorted.hpp>

namespace jln::mp::smp
{
  template<class Cmp = less<>, class C = identity>
  using is_sorted = contract<
    mp::if_<
      mp::size<mp::less_than_c<2>>,
      mp::always<true_, assume_positive_number<C>>,
      mp::if_<
        mp::size<mp::is<number<2>>>,
        mp::tee<assume_binary<Cmp>, as_bool<C>>,
        partial_drop_until_xs_c<
          -2,
          contract<detail::bind_and_flip_2<assume_binary<Cmp>>>,
          contract<mp::always<false_, assume_positive_number<C>>>,
          contract<mp::always<true_, assume_positive_number<C>>>
        >
      >
    >
  >;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Cmp, class C>
  struct _sfinae<sfinae, is_sorted<Cmp, C>>
  {
    using type = smp::is_sorted<sfinae<Cmp>, sfinae<C>>;
  };
}
/// \endcond
