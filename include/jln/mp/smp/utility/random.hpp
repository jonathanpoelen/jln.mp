// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/random.hpp>

#ifdef __cpp_generic_lambdas
#if __cpp_generic_lambdas >= 201707L

namespace jln::mp::smp
{
  template<class Tag = default_make_index_tag, class C = identity, auto v = []{}>
  using random_for = contract<mp::random_for<Tag, assume_positive_number<C>, v>>;

  template<class C = identity, auto v = []{}>
  using random = contract<
    mp::random_for<default_make_index_tag, assume_positive_number<C>, v>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Tag, class C, auto v>
  struct _sfinae<sfinae, random_for<Tag, C, v>>
  {
    using type = contract<mp::random_for<Tag, assume_positive_number<C>, v>>;
  };

  template<class Tag, class C, auto v>
  struct expected_argument<random_for<Tag, C, v>>
  : number<argument_category::unary_or_more>
  {};
}
/// \endcond

#endif
#endif
