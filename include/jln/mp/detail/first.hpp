// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/config.hpp>
#include <jln/mp/list/list.hpp>

#include <cstddef>


namespace jln::mp::detail
{
  template<class x, std::size_t>
  struct first
  {
    using type = x;
  };

#if JLN_MP_FORCE_LAZY_ALIAS
# define JLN_MP_LAZY_PARAM(deps, ...) __VA_ARGS__
# define JLN_MP_LAZY_PARAM_T(deps, ...) __VA_ARGS__
#elif JLN_MP_ENABLE_TYPE_PACK_ELEMENT
# define JLN_MP_LAZY_PARAM(deps, ...) __type_pack_element<0, __VA_ARGS__, deps>
# define JLN_MP_LAZY_PARAM_T(deps, ...) __type_pack_element<0, __VA_ARGS__, deps>
#else
# define JLN_MP_LAZY_PARAM(deps, ...) \
  ::jln::mp::detail::first<__VA_ARGS__, sizeof(::jln::mp::list<deps>)>::type
# define JLN_MP_LAZY_PARAM_T(deps, ...) \
  typename JLN_MP_LAZY_PARAM(deps, __VA_ARGS__)
#endif
}
