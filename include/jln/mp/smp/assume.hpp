#pragma once

#include "contract.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class F> struct _assume_number { using type = F; };
    template<class F> struct _assume_positive_number { using type = F; };
    template<class F> struct _assume_numbers { using type = F; };
    template<class F> struct _assume_unary { using type = F; };
    template<class F> struct _assume_unary_or_more { using type = F; };
    template<class F> struct _assume_binary { using type = F; };
    template<class F> struct _assume_binary_list { using type = F; };
    template<class F> struct _assume_binary_or_more { using type = F; };
    template<class F> struct _assume_lists { using type = F; };
  }

  template<class C>
  using assume_number = typename detail::_assume_number<subcontract<C>>::type;

  template<class C>
  using assume_positive_number = typename detail::_assume_positive_number<subcontract<C>>::type;

  template<class C>
  using assume_numbers = typename detail::_assume_numbers<subcontract<C>>::type;

  template<class C>
  using assume_unary = typename detail::_assume_unary<subcontract<C>>::type;

  template<class C>
  using assume_binary = typename detail::_assume_binary<subcontract<C>>::type;

  template<class C>
  using assume_binary_list = typename detail::_assume_binary_list<subcontract<C>>::type;

  template<class C>
  using assume_lists = typename detail::_assume_lists<subcontract<C>>::type;

  template<class C>
  using assume_binary_or_more = typename detail::_assume_binary_or_more<subcontract<C>>::type;

  template<class C>
  using assume_unary_or_more = typename detail::_assume_unary_or_more<subcontract<C>>::type;


  template<class F, class TC = identity, class FC = violation>
  using try_assume_unary_or_more = typename detail::_optimize_try_invoke<
    try_invoke<assume_unary_or_more<F>, TC, FC>>::type;

  template<class F, class TC = identity, class FC = violation>
  using try_assume_unary = typename detail::_optimize_try_invoke<
    try_invoke<assume_unary<F>, TC, FC>>::type;

  template<class F, class TC = identity, class FC = violation>
  using try_assume_binary = typename detail::_optimize_try_invoke<
    try_invoke<assume_binary<F>, TC, FC>>::type;

  template<class F>
  using assume_unary_barrier = contract_barrier<assume_unary<F>>;

  template<class F>
  using assume_binary_barrier = contract_barrier<assume_binary<F>>;

  template<class F>
  using assume_number_barrier = contract_barrier<assume_number<F>>;

  template<class F>
  using assume_binary_list_barrier = contract_barrier<assume_binary_list<F>>;
}


/// \cond
namespace jln::mp::detail
{
  template<class F>
  struct expected_argument : number<0>
  {};

#define JLN_MP_UNPACK(...) __VA_ARGS__

#define JLN_MP_MAKE_EXPECTED_ARGUMENT(expected, tpl, spe) \
  template<JLN_MP_UNPACK tpl>                             \
  struct expected_argument<JLN_MP_UNPACK spe>             \
  : number<expected>                                      \
  {}

#define JLN_MP_MAKE_EXPECTED_ARGUMENT1(expected, name) \
  template<class C>                                    \
  struct expected_argument<name<C>>                    \
  : number<expected>                                   \
  {}

#define JLN_MP_MAKE_EXPECTED_ARGUMENT2(expected, name) \
  template<class F, class C>                           \
  struct expected_argument<name<F, C>>                 \
  : number<expected>                                   \
  {}

  struct argument_category
  {
    enum tag
    {
      lists             = 1 << 0,
      number            = 1 << 1,
      positive_number   = 1 << 2,
      unary             = 1 << 3,
      binary            = 1 << 4,
      unary_or_more     = 1 << 5,
      binary_or_more    = 1 << 6,
      binary_list       = 1 << 7,
      numbers           = 1 << 8,

      _unary            = unary,
      _binary           = binary,
      _binary_or_more   = _binary | binary_or_more | binary_list,
      _unary_or_more    = _unary | unary_or_more | _binary_or_more,
      _positive_number  = positive_number | _unary | number,
      _number           = number | _positive_number,
      _numbers          = _number | numbers,
      _lists            = lists,
      _binary_list      = binary_list | _binary,
    };
  };

#define JLN_MP_MK_ASSUME(cat)                                 \
  template<class F>                                           \
  struct _assume_##cat<try_invoke<F, identity, violation>>    \
  {                                                           \
    using type = typename conditional_c<bool(                 \
      expected_argument<F>::value & argument_category::_##cat \
    )>::template f<F, try_invoke<F, identity, violation>>;    \
  }

  JLN_MP_MK_ASSUME(lists);
  JLN_MP_MK_ASSUME(numbers);
  JLN_MP_MK_ASSUME(number);
  JLN_MP_MK_ASSUME(positive_number);
  JLN_MP_MK_ASSUME(unary);
  JLN_MP_MK_ASSUME(binary);
  JLN_MP_MK_ASSUME(binary_list);
  JLN_MP_MK_ASSUME(unary_or_more);
  JLN_MP_MK_ASSUME(binary_or_more);

#undef JLN_MP_MK_ASSUME
}
/// \endcond
