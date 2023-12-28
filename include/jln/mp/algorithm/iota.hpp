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
    template<int_ start, int_ count, int_ stride, bool is_neg = 0 < count>
    struct iota_v_c;
  }
  /// \endcond

  /// \ingroup number

  /// Generates a sequence of \int_.
  /// \treturn \sequence of \int_
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
    template<int_ start, int_ count, int_ stride = 1, class C = mp::numbers<>>
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

    template<int_ start, int_ count, int_ stride = 1, class C = mp::listify>
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
  template<int_... i>
  struct iota_c_result;

  template<class, int_... i>
  struct iota_impl
  {
    template<int_ start, int_ stride>
    using strided = iota_c_result<start + i * stride...>;
  };

  template<int_ start, int_ count, int_ stride, bool is_neg>
  struct iota_v_c
    : JLN_MP_MAKE_INTEGER_SEQUENCE(count < 0 ? -count : count, iota_impl)
    ::template strided<start, count < 0 ? -stride : stride>
  {};

#if JLN_MP_MEMOIZED_ALIAS
  template<int_... i>
  struct iota_c_result
  {
    template<class C>
    using f = typename JLN_MP_CALLER_TRACE_XS(i, C)::template f<i...>;
  };

  template<int_ count>
  struct iota_v_c<0, count, 1, false>
  {
    template<class C>
    using f = emp::make_int_sequence_v_c<count, C>;
  };
#else
  template<int_... i>
  struct iota_c_result
  {
    template<class C>
    struct f
    {
      using type = typename JLN_MP_CALLER_TRACE_XS(i, C)::template f<i...>;
    };
  };

  template<int_ count>
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
