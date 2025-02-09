// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/functional/call.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/value/val.hpp>

#if JLN_MP_ENABLE_TPL_AUTO && (!JLN_MP_DEBUG || JLN_MP_CLANG_LIKE)
namespace jln::mp
{
  /// \ingroup value

  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<xs::value>...);
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, val<T(xs::value)>...);
  };

  namespace emp
  {
    template<auto... xs>
    using values = list<val<xs>...>;

    template<class T, T... xs>
    using typed_values = list<val<T(xs)>...>;
  }
} // namespace jln::mp
#else
namespace jln::mp
{
  template<class C = listify>
  struct values
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, value_from<xs>...);
  };

  template<class C = listify>
  struct typed_values
  {
    template<class T, class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, typed_value<T, xs::value>...);
  };

  namespace emp
  {
    template<int_t... xs>
    using values = list<typed_value<int_t, xs>...>;

    template<class T, T... xs>
    using typed_values = list<typed_value<T, xs>...>;
  }
}
#endif
