// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/contract.hpp>
#include <jln/mp/functional/memoize.hpp>

namespace jln::mp
{
  namespace detail
  {
#define JLN_MP_MK_ASSUME(name)                         \
    template<class F> struct name { using type = F; }; \
    template<class F> struct name<memoize<F>>          \
    {                                                  \
      using type = memoize<typename name<F>::type>;    \
    }

    JLN_MP_MK_ASSUME(_assume_number);
    JLN_MP_MK_ASSUME(_assume_positive_number);
    JLN_MP_MK_ASSUME(_assume_numbers);
    JLN_MP_MK_ASSUME(_assume_unary);
    JLN_MP_MK_ASSUME(_assume_unary_or_more);
    JLN_MP_MK_ASSUME(_assume_binary);
    JLN_MP_MK_ASSUME(_assume_binary_list);
    JLN_MP_MK_ASSUME(_assume_binary_or_more);
    JLN_MP_MK_ASSUME(_assume_lists);
#undef JLN_MP_MK_ASSUME
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


  template<class F>
  using assume_lists_barrier = contract<assume_lists<F>>;

  template<class F>
  using assume_unary_barrier = contract<assume_unary<F>>;

  template<class F>
  using assume_binary_barrier = contract<assume_binary<F>>;

  template<class F>
  using assume_number_barrier = contract<assume_number<F>>;

  template<class F>
  using assume_positive_number_barrier = contract<assume_positive_number<F>>;

  template<class F>
  using assume_binary_list_barrier = contract<assume_binary_list<F>>;

  template<class F>
  using assume_lists_barrier = contract<assume_lists<F>>;

  template<class F>
  using assume_binary_or_more_barrier = contract<assume_binary_or_more<F>>;

  template<class F>
  using assume_unary_or_more_barrier = contract<assume_unary_or_more<F>>;
}


/// \cond
#include <jln/mp/detail/unpack.hpp>
#include <jln/mp/list/is_list.hpp>
#include <jln/mp/algorithm/all_of.hpp>

namespace jln::mp::detail
{
  template<class F>
  struct expected_argument : number<0>
  {};

  template<class F>
  struct expected_argument<memoize<F>> : expected_argument<F>
  {};

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

#define JLN_MP_MAKE_EXPECTED_ARGUMENT3(expected, name) \
  template<class G, class F, class C>                  \
  struct expected_argument<name<G, F, C>>              \
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
    };
  };

  struct _expected_argument_category : argument_category
  {
    enum tag
    {
      _lists            = lists,
      _numbers          = numbers,
      _number           = number | numbers | unary | unary_or_more,
      _positive_number  = positive_number | number | numbers | unary | unary_or_more,
      _unary            = unary | unary_or_more,
      _binary           = binary | unary_or_more | binary_or_more,
      _binary_list      = binary_list | lists | binary | unary_or_more | binary_or_more,
      _unary_or_more    = unary_or_more,
      _binary_or_more   = binary_or_more | unary_or_more,
    };
  };

#define JLN_MP_MK_ASSUME(cat)                        \
  template<class F>                                  \
  struct _assume_##cat<try_<F, identity, violation>> \
  {                                                  \
    using type = typename conditional_c<bool(        \
      expected_argument<F>::value                    \
      & _expected_argument_category::_##cat          \
    )>::template f<F, try_<F, identity, violation>>; \
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

  template<class TC>
  struct _assume_lists<if_<all_of<is_list<>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_unary_or_more<if_<size<>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_unary_or_more<if_<is<number<0>, not_<>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_unary<if_<size<is<number<1>>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_binary<if_<size<is<number<2>>>, TC, violation>>
  {
    using type = TC;
  };

  template<class TC>
  struct _assume_binary_or_more<if_<size<is<number<2>>>, TC, violation>>
  {
    using type = TC;
  };
}
/// \endcond
