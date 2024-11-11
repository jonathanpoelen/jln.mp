// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/numbers.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_t start, int_t count, int_t stride, bool is_neg = 0 < count>
    struct iota_v_c;
  }
  /// \endcond

  /// \ingroup number

  /// Generates a sequence of \int_t.
  /// \treturn \sequence of \int_t
  /// \see iota
  template<class C = numbers<>>
  struct iota_v
  {
    template<class start, class count, class stride = number<1>>
    using f = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;
  };

  /// \ingroup number

  /// Generates a sequence of \number.
  /// \treturn \sequence of number
  template<class C = listify>
  using iota = iota_v<numbers<C>>;

  namespace emp
  {
    template<int_t start, int_t count, int_t stride = 1, class C = mp::numbers<>>
    using iota_v_c = typename detail::iota_v_c<start, count, stride>::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<class start, class count, class stride = number<1>, class C = mp::numbers<>>
    using iota_v = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<C>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<int_t start, int_t count, int_t stride = 1, class C = mp::listify>
    using iota_c = typename detail::iota_v_c<start, count, stride>::template f<mp::numbers<C>>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;

    template<class start, class count, class stride = number<1>, class C = mp::listify>
    using iota = typename detail::iota_v_c<start::value, count::value, stride::value>
      ::template f<mp::numbers<C>>
      #if !JLN_MP_MEMOIZED_ALIAS
      ::type
      #endif
      ;
  }
}

#include <jln/mp/algorithm/make_int_sequence.hpp>

/// \cond
namespace jln::mp::detail
{
  template<int_t... i>
  struct iota_c_result;

  template<class, int_t... i>
  struct iota_impl
  {
    template<int_t start, int_t stride>
    using strided = iota_c_result<start + i * stride...>;
  };

  template<int_t start, int_t count, int_t stride, bool is_neg>
  struct iota_v_c
    : JLN_MP_MAKE_INTEGER_SEQUENCE(count < 0 ? -count : count, iota_impl)
    ::template strided<start, count < 0 ? -stride : stride>
  {};

#if JLN_MP_MEMOIZED_ALIAS
  template<int_t... i>
  struct iota_c_result
  {
    template<class C>
    using f = typename JLN_MP_CALLER_XS(i, C)::template f<i...>;
  };

  template<int_t count>
  struct iota_v_c<0, count, 1, false>
  {
    template<class C>
    using f = emp::make_int_sequence_v_c<count, C>;
  };
#else
  template<int_t... i>
  struct iota_c_result
  {
    template<class C>
    struct f
    {
      using type = typename JLN_MP_CALLER_XS(i, C)::template f<i...>;
    };
  };

  template<int_t count>
  struct iota_v_c<0, count, 1, false>
  {
    template<class C>
    struct f
    {
      using type = emp::make_int_sequence_v_c<count, C>;
    };
  };
#endif
}
/// \endcond
