#pragma once

#include "../number/number.hpp"
#include "../utility/conditional.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class F> struct _assume_number { using type = F; };
    template<class F> struct _assume_positive { using type = F; };
    template<class F> struct _assume_strictly_positive { using type = F; };
    template<class F> struct _assume_list { using type = F; };
    template<class F> struct _assume_binary_number { using type = F; };
    template<class F> struct _assume_binary_positive { using type = F; };
    template<class F> struct _assume_binary_strictly_positive { using type = F; };
    template<class F> struct _assume_binary_list { using type = F; };
    template<class F> struct _assume_xs_number { using type = F; };
    template<class F> struct _assume_xs_positive { using type = F; };
    template<class F> struct _assume_xs_strictly_positive { using type = F; };
    template<class F> struct _assume_xs_list { using type = F; };
  }

  template<class F>
  using assume_number = typename detail::_assume_number<F>::type;

  template<class F>
  using assume_positive = typename detail::_assume_positive<F>::type;

  template<class F>
  using assume_strictly_positive = typename detail::_assume_strictly_positive<F>::type;

  template<class F>
  using assume_list = typename detail::_assume_list<F>::type;

  template<class F>
  using assume_binary_number = typename detail::_assume_binary_number<F>::type;

  template<class F>
  using assume_binary_positive = typename detail::_assume_binary_positive<F>::type;

  template<class F>
  using assume_binary_strictly_positive = typename detail::_assume_binary_strictly_positive<F>::type;

  template<class F>
  using assume_binary_list = typename detail::_assume_binary_list<F>::type;

  template<class F>
  using assume_xs_number = typename detail::_assume_xs_number<F>::type;

  template<class F>
  using assume_xs_positive = typename detail::_assume_xs_positive<F>::type;

  template<class F>
  using assume_xs_strictly_positive = typename detail::_assume_xs_strictly_positive<F>::type;

  template<class F>
  using assume_xs_list = typename detail::_assume_xs_list<F>::type;
}

namespace jln::mp::detail
{
  struct argument_category
  {
    enum tag
    {
      strictly_positive = 0b000'0001,
      positive          = 0b000'0010,
      number            = 0b000'0100,
      list              = 0b000'1000,

      _positive         = positive | strictly_positive,
      _number           = number | _positive,

      unary             = 0b001'0000,
      binary            = 0b010'0000,
      variadic          = 0b100'0000,

      unary_strictly_positive = unary | strictly_positive,
      unary_positive = unary | positive,
    };
  };

  template<class F>
  struct expected_argument : number<0>
  {};

  // TODO != number -> violation ?
  template<class F>
  using _assume_number_cond = conditional_c<(
    (expected_argument<F>::value
      & (detail::argument_category::_number
        | detail::argument_category::unary)
    ) > detail::argument_category::unary
  )>;
}
