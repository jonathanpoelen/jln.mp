// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/expr_to_bool.hpp>

namespace jln::mp
{
  /// \ingroup utility

  template<bool>
  struct conditional_c;

  template<>
  struct conditional_c<true>
  {
    template<class true_value, class false_value>
    using f = true_value;
  };

  template<>
  struct conditional_c<false>
  {
    template<class true_value, class false_value>
    using f = false_value;
  };

  template<class bool_>
  using conditional = conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(bool_::value)>;

  namespace emp
  {
#if !JLN_MP_ENABLE_TYPE_PACK_ELEMENT
    template<class bool_, class true_value, class false_value>
    using conditional = typename mp::conditional_c<JLN_MP_RAW_EXPR_TO_BOOL(bool_::value)>
      ::template f<true_value, false_value>;

    template<bool bool_, class true_value, class false_value>
    using conditional_c = typename mp::conditional_c<bool_>
      ::template f<true_value, false_value>;
#else
    template<class bool_, class true_value, class false_value>
    using conditional = __type_pack_element<
      JLN_MP_RAW_EXPR_TO_BOOL(bool_::value), false_value, true_value
    >;

    template<bool bool_, class true_value, class false_value>
    using conditional_c = __type_pack_element<bool_, false_value, true_value>;
#endif
  }

// The gcc version is somewhat buggy and does not support chaining.
// __type_pack_element<i, a, b>::type // error
#if JLN_MP_ENABLE_TYPE_PACK_ELEMENT
# define JLN_MP_CONDITIONAL_P_C_T(b, true_value, false_value) \
  __type_pack_element<JLN_MP_UNPACK b, JLN_MP_UNPACK false_value, JLN_MP_UNPACK true_value>
# define JLN_MP_CONDITIONAL_C_T(b, true_value, false_value) \
  __type_pack_element<b, false_value, true_value>
#else
# define JLN_MP_CONDITIONAL_P_C_T(b, true_value, false_value) \
  typename ::jln::mp::conditional_c<JLN_MP_UNPACK b>          \
  ::template f<JLN_MP_UNPACK true_value, JLN_MP_UNPACK false_value>
# define JLN_MP_CONDITIONAL_C_T(b, true_value, false_value) \
  typename ::jln::mp::conditional_c<b>::template f<true_value, false_value>
#endif

} // namespace jln::mp
