// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/utility/make_index.hpp>

#if JLN_MP_ENABLE_FRIEND_INJECTION && JLN_MP_FEATURE_CONCEPTS

namespace jln::mp::smp
{
  template<class Tag = default_make_index_tag, class C = identity>
  using make_index_for = try_contract<mp::make_index_for<Tag, assume_positive_number<C>>>;

  template<class C = identity>
  using make_index = try_contract<mp::make_index_for<default_make_index_tag, assume_positive_number<C>>>;
}

/// \cond
namespace jln::mp::detail
{
  template<template<class> class sfinae, class Tag, class C>
  struct _sfinae<sfinae, make_index_for<Tag, C>>
  {
    using type = smp::make_index_for<Tag, C>;
  };

  JLN_MP_MAKE_EXPECTED_ARGUMENT2(argument_category::unary, make_index_for);
}
/// \endcond

#endif
