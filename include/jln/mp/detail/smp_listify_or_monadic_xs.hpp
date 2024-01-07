// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/functional/monadic.hpp>
#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/smp/assume.hpp>

namespace jln::mp::detail
{
  struct smp_monadic_xs
  {
    template<class C>
    using f = monadic_xs<subcontract<C>>;
  };

  struct smp_assume_lists
  {
    template<class C>
    using f = assume_lists<C>;
  };

  template<class, class = listify>
  struct smp_listify_or_monadic_xs : smp_monadic_xs
  {};

  template<>
  struct smp_listify_or_monadic_xs<listify, listify> : smp_assume_lists
  {};

  template<>
  struct smp_listify_or_monadic_xs<listify, contract<listify>> : smp_assume_lists
  {};

  template<>
  struct smp_listify_or_monadic_xs<contract<listify>, contract<listify>> : smp_assume_lists
  {};

  template<>
  struct smp_listify_or_monadic_xs<contract<listify>, listify> : smp_assume_lists
  {};
}
/// \endcond
