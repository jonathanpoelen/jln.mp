// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/map/map_update.hpp>
#include <jln/mp/map/map_replace.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct smp_map_replace;
}
/// \endcond

namespace jln::mp::smp
{
  template<class KV, class C = listify>
  using map_replace = typename detail::smp_map_replace<mp::is_map<>::f<KV>>
    ::template f<KV, C>;

  template<class KV, class C = listify>
  using map_replace_or_insert = typename detail::smp_map_update_or_insert<mp::is_map<>::f<KV>>
    ::template f<KV, contract<mp::always<KV>>, C>;
}

#include <jln/mp/smp/map/map_find.hpp> // contains _sfinae<..., map_replace>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_map_replace<true_>
  {
    template<class KV, class C>
    using f = test_contract<
      mp::is_map<>,
      mp::map_replace<KV, assume_unary_or_more<C>>
    >;
  };

  template<>
  struct smp_map_replace<false_>
    : always<bad_contract>
  {};
}
/// \endcond
