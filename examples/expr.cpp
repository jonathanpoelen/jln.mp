#include <jln/mp/algorithm/contains.hpp>
#include <jln/mp/algorithm/count.hpp>
#include <jln/mp/algorithm/repeat.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/unique.hpp>
#include <jln/mp/functional/if.hpp>
#include <jln/mp/functional/lift.hpp>
#include <jln/mp/list/at.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/list/size.hpp>
#include <jln/mp/list/wrap_in_list.hpp>

#include <functional>

namespace mp = jln::mp;

template<class T, class Var = void>
struct Value
{
  T value;

  template<class Values>
  T eval(Values const&) const
  {
    return value;
  }
};

template<class Var, class T>
T to_value(Value<T, Var> value)
{
  return value.value;
}

template<char... c>
struct Var
{
  template<class Values>
  static auto eval(Values values)
  {
    return to_value<Var<c...>>(values);
  }

  Var() = default;
  Var(Var const&) = default;
  Var& operator=(Var const&) = default;

  template<class T>
  Value<T, Var> operator=(T x)
  {
    return {x};
  }
};

template<class Fn, class Operand1, class Operand2>
struct Expression
{
  Fn fn;
  Operand1 operand1;
  Operand2 operand2;

  template<class Values>
  auto eval(Values values) const
  {
    return fn(operand1.eval(values), operand2.eval(values));
  }
};

template<class Var>
struct is_var : std::false_type
{};

template<char... c>
struct is_var<Var<c...>> : std::true_type
{};

template<class Expr>
struct is_expression : std::false_type
{};

template<class... Ts>
struct is_expression<Expression<Ts...>> : std::true_type
{};

template<class T>
using to_expr_type = mp::if_<
  mp::lift<is_expression>,
  mp::identity,
  mp::if_<
    mp::lift<is_var>,
    mp::identity,
    mp::lift<Value>
  >
>::f<T>;

template<class T, class U>
Expression<std::plus<>, to_expr_type<T>, to_expr_type<U>> operator+(T a, U b)
{
  return {{}, {a}, {b}};
}

template<class T, class U>
Expression<std::multiplies<>, to_expr_type<T>, to_expr_type<U>> operator*(T a, U b)
{
  return {{}, {a}, {b}};
}


namespace detail
{

// recursively extract all variables
struct extract_vars : mp::unpack<
  mp::transform<
    mp::if_<
      mp::lift<is_expression>,
      extract_vars, // recursivity
      mp::wrap_in_list_if<mp::lift<is_var>>
    >,
    mp::join<>
  >
> {};

// tuple of value (faster than std::tuple)
template<class... Value>
struct values : Value...
{};

template<class ExprVariables, class ValueVariables,
  class SingleValueVariables = mp::emp::unique<ValueVariables>,
  class AllVariables = mp::join<mp::unique<>>::f<ExprVariables, SingleValueVariables>,
      // all variables must be in the expression
  bool = std::is_same_v<ExprVariables, AllVariables>
      // values must not be duplicate
      && std::is_same_v<ValueVariables, SingleValueVariables>
      // all values refer to a variable and vice versa
      && mp::emp::size<ExprVariables>::value == mp::emp::size<SingleValueVariables>::value>
struct values_factory
{
  template<class... Values>
  using values_type = values<Values...>;
};

namespace error
{
  template<class... Ts>
  class missing_variables
  {
    static_assert(!sizeof...(Ts), "variables are missing");
  };

  template<class... Ts>
  class too_many_variables
  {
    static_assert(!sizeof...(Ts), "too much value");
  };

  template<class... Ts>
  class duplicate_variables
  {
    static_assert(!sizeof...(Ts), "duplicate variables");
  };
}

template<template<class...> class Error, class L, class... Ts>
using extract_unknown_variables = mp::call<
  mp::join<mp::lift<Error>>,
  mp::call<
    mp::conditional<
      mp::emp::contains<L, Ts>
    >,
    mp::list<>,
    mp::list<Ts>
  >...
>;

template<class... ExprVariable, class... ValueVariable, class... SingleValueVariable, class AllVariables>
struct values_factory<
  mp::list<ExprVariable...>,
  mp::list<ValueVariable...>,
  mp::list<SingleValueVariable...>,
  AllVariables, false
>
  : extract_unknown_variables<error::missing_variables, mp::list<ValueVariable...>, ExprVariable...>
  , extract_unknown_variables<error::too_many_variables, mp::list<ExprVariable...>, ValueVariable...>
  , mp::join<mp::lift<error::duplicate_variables>>::f<
      mp::call<mp::repeat_c<
        mp::call<mp::count<SingleValueVariable>, ValueVariable...>::value - 1
      >, SingleValueVariable>
    ...>
{};

}

template<class Expr, class... Values>
auto eval(Expr expr, Values... values)
{
  using expr_variables = mp::emp::unique<detail::extract_vars::f<Expr>>;
  using value_variables = mp::list<mp::unpack<mp::at1<>>::f<Values>...>;
  using factory = detail::values_factory<expr_variables, value_variables>;
  using values_type = typename factory::template values_type<Values...>;
  return expr.eval(values_type{values...});
}


#include <cstdio>

int main()
{
  Var<'a'> a;
  Var<'b'> b;
  auto expr = (a + b) * (2 + a);
  std::printf("%d\n", eval(expr, a=3, b=4)); // 35

  // Var<'c'> c;
  // std::printf("%d\n", eval(expr, b=4)); // error::missing_variables<Var<'a'>>
  // std::printf("%d\n", eval(expr, c=2, a=3, b=4)); // error::too_many_variables<Var<'c'>>
  //std::printf("%d\n", eval(expr, a=3, b=4, b=2)); // error::duplicate_variables<Var<'b'>>
}
