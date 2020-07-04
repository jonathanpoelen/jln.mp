[![CI](https://github.com/jonathanpoelen/jln.mp/workflows/CI/badge.svg?branch=master&event=push)](https://github.com/jonathanpoelen/jln.mp/actions?query=workflow%3ACI)

[Jln.mp](https://github.com/jonathanpoelen/jln.mp) is a single header C++17 metaprogramming library designed for fast compilation speed.

Licence: MIT

Online documentation: https://jonathanpoelen.github.io/jln.mp/

Single file version in [standalone branch](https://github.com/jonathanpoelen/jln.mp/tree/standalone).

# Concepts

Functions of jln.mp are used in 2 stages:

- Instantiation, by indicating parameters which describe how it must work.
- Call, by applying sequence to an instantiation.

For example, suppose we want to remove `void` from a sequence. The function to use is `jln::mp::remove`:

```cpp
using foo = jln:mp::remove<void>;
```

We can then apply it to our data:

```cpp
using result = jln::mp::call<foo, int, void, double, char>;
// result == jln::mp::list<int, double, char>
```

Now suppose that `result` must be a `std::tuple`. Rather than linking with another function, it is possible to combine them in `foo` via a continuation (`C` parameter).

```cpp
using foo = jln:mp::remove<void, /*C=*/jln::mp::cfe<std::tuple>>;

using result = jln::mp::call<foo, int, void, double, char>;
// result == std::tuple<int, double, char>
```

The default continuations are `jln::mp::listify` which transforms a sequence into a `jln::mp::list` and `jln::mp::identity` which returns the input value.


Jln.mp also has 2 additional namespaces:

- `smp` a SFINAE compatible version of `mp`.
- `emp` which directly returns a result without going through `jln::mp::call`. According to the function, type sequences are replaced by lists and continuations are not available.


## Create a function

A function is a type with a `f` template member.

```cpp
struct to_tuple
{
  template<class... xs>
  using f = std::tuple<xs...>;
};

jln::mp::call<to_tuple, int, double> == std::tuple<int, double>
```

In the mind of the library, functions should at least take a continuation.

```cpp
template<class C = jln::mp::identity>
struct to_tuple
{
  template<class... xs>
  using f = jln::mp::call<C, std::tuple<xs...>>;
};

jln::mp::call<to_tuple<>, int, double> == std::tuple<int, double>
```


# Glossary

- Sequence: a value sequence or a type sequence.
- Value: a type with a `value` member.
- Typelist: an instance compatible with `template<class...> class T`, such as `list<>`.
- Function: a type with a `f` template member. The number and the nature of the parameters depend on the context of use.
- Meta-function: a template class `template<class...> class M`.
- Lazy meta-function: a meta-function with a `type` member.
- `C`: Continuation function. Represents the function used to chain calls, typically `listify` or `identity`.
- `_v` suffix: `C::f` takes values. Usually `C::f<jln::mp::int_...>` (C++17) or `C::f<auto...>` (C++20).
- `_c` suffix: number type parameters are `jln::mp::int_`. Usually `foo_c<int_ i> = foo<number<i>>`.


# Example of real life

Implementation of `std::tuple_cat` that works with tuple like.

```cpp
#include "jln/mp/algorithm/make_int_sequence.hpp"
#include "jln/mp/algorithm/transform.hpp"
#include "jln/mp/algorithm/repeat.hpp"
#include "jln/mp/functional/each.hpp"
#include "jln/mp/functional/lift.hpp"
#include "jln/mp/list/as_list.hpp"
#include "jln/mp/list/join.hpp"
#include "jln/mp/list/at.hpp"

#include <tuple>

namespace mp = jln::mp;
namespace emp = jln::mp::emp;

template<class Tuple>
struct my_tuple_element
{
    template<class I>
    using f = std::tuple_element_t<I::value, Tuple>;
};

template<class... Tuples>
using my_tuple_cat_result_type = mp::call<
    // convert a sequence of mp::list to std::tuple
    mp::join<mp::lift<std::tuple>>,
    // convert a tuple like to mp::list
    emp::make_int_sequence<
        std::tuple_size<std::remove_reference_t<Tuples>>,
        // convert a sequence of tuple index to a mp::list of tuple element
        mp::transform<my_tuple_element<std::decay_t<Tuples>>>
    >...
>;

template<mp::int_... ituples, mp::int_... ivalues, class... Tuples>
constexpr auto my_tuple_cat_impl(
    emp::numbers<ituples...>, emp::numbers<ivalues...>, std::tuple<Tuples...> t)
{
    // get is looked up by argument-dependent lookup
    using std::get;
    return my_tuple_cat_result_type<Tuples...>{
        get<ivalues>(get<ituples>(t))...
    };
}

template<class... Tuples, class R = my_tuple_cat_result_type<Tuples...>>
constexpr R my_tuple_cat(Tuples&&... args)
{
    // ex:    tuple_size=3     tuple_size=2     tuple_size=4
    // list<    0, 0, 0,                 1, 1,             2, 2, 2, 2 >
    using index_by_tuple = emp::make_int_sequence_c<
        sizeof...(Tuples),
        // repeat each index by number of element
        mp::each<mp::repeat<std::tuple_size<std::remove_reference_t<Tuples>>>...,
            mp::join<>
        >
    >;

    // ex:    tuple_size=3     tuple_size=2     tuple_size=4
    // list<    0, 1, 2,                 0, 1,             0, 1, 2, 3 >
    using index_by_value = emp::join<
        emp::make_int_sequence<std::tuple_size<std::remove_reference_t<Tuples>>>...
    >;

    return my_tuple_cat_impl(index_by_tuple{}, index_by_value{}, std::tuple<Tuples&&...>(args...));
}

// defines a tuple like
//@{
namespace toy
{
    // tuple like
    struct Vector2D
    {
        int x, y;
    };

    template<std::size_t i>
    constexpr int get(Vector2D const& t)
    {
        return i == 0 ? t.x : t.y;
    }
}

template<>
struct std::tuple_size<::toy::Vector2D>
: std::integral_constant<std::size_t, 2>
{};

template<size_t i>
struct std::tuple_element<i, ::toy::Vector2D>
{
    using type = int;
};
//@}

// test
// @{
constexpr std::tuple<int, float, double> t0{1, 2, 3};
constexpr std::tuple<char, unsigned> t1{4, 5};
constexpr std::tuple<long> t2{6};
constexpr std::array<short, 4> a{7, 8, 9, 10};
constexpr toy::Vector2D v {11, 12};

constexpr auto my_tuple = my_tuple_cat(t0, t1, t2, a, v);

using my_tuple_type = std::remove_const_t<decltype(my_tuple)>;
using std_tuple = std::tuple<
    int, float, double,
    char, unsigned,
    long,
    short, short, short, short,
    int, int>;

static_assert(std::is_same_v<my_tuple_type, std_tuple>);
static_assert(my_tuple == std::tuple{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
// @}
```

# FAQ

> Functions are missing in the stacktrace when the compiler displays an error message, how to display them?

Compile with the define `JLN_MP_ENABLE_DEBUG` at `1` to have errors with more context.

> Error: `sorry, unimplemented: mangling record_type` or `sorry, unimplemented: mangling typename_type` with Gcc.

This is a [Gcc bug](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=95299) when an algorithm is used in the prototype of a function.

```cpp
template<class... Ts>
mp::call<func, Ts...> foo();

// Must be replaced by

template<class... Ts, class R = mp::call<func, Ts...>>
R foo();
```
