// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/list/listify.hpp>
#include <jln/mp/map/is_map.hpp>
#include <jln/mp/map/map_insert.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class>
  struct smp_map_insert;
}
/// \endcond

namespace jln::mp::smp
{
  template<class KV, class C = listify>
  using map_insert = typename detail::smp_map_insert<mp::is_map<>::f<KV>>
    ::template f<KV, C>;
}

#include <jln/mp/smp/map/map_find.hpp> // contains _sfinae<..., map_insert>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct smp_map_insert<true_>
  {
    template<class KV, class C>
    using f = test_contract<
      mp::is_map<>,
      mp::map_insert<KV, assume_unary_or_more<C>>
    >;
  };

  template<>
  struct smp_map_insert<false_>
    : always<bad_contract>
  {};
}
/// \endcond
