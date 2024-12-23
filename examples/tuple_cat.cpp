// Implementation of `std::tuple_cat` that works with tuple like.

#include "jln/mp/algorithm/make_int_sequence.hpp"
#include "jln/mp/algorithm/transform.hpp"
#include "jln/mp/algorithm/repeat.hpp"
#include "jln/mp/algorithm/repeat_index.hpp"
#include "jln/mp/functional/each.hpp"
#include "jln/mp/functional/lift.hpp"
#include "jln/mp/list/join.hpp"

#include <array>
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
    // Convert a sequence of mp::list to std::tuple
    mp::join<mp::lift<std::tuple>>,
    // Convert a tuple like to mp::list of tuple element.
    // To support tuple-likes, it is necessary to use std::tuple_size and std::tuple_element.
    // Otherwise, emp::unpack<Tuples> is sufficient.
    emp::make_int_sequence<
        std::tuple_size<std::decay_t<Tuples>>,
        // Convert a sequence of tuple index to a mp::list of tuple element.
        mp::transform<my_tuple_element<std::decay_t<Tuples>>>
    >...
>;

template<class R, mp::int_t... ituples, mp::int_t... ivalues, class Tuple>
constexpr R my_tuple_cat_impl(
    emp::numbers<ituples...>, emp::numbers<ivalues...>, Tuple t)
{
    // get is looked up by argument-dependent lookup
    using std::get;
    return R{ get<ivalues>(get<ituples>(std::move(t)))... };
}

template<class... Tuples, class R = my_tuple_cat_result_type<Tuples...>>
constexpr R my_tuple_cat(Tuples&&... args)
{
    // ex:    tuple_size=3     tuple_size=2     tuple_size=4
    // list<    0, 0, 0,           1, 1,         2, 2, 2, 2   >
    using index_by_tuple = mp::repeat_index_v_c<mp::join<>>
        ::f<std::tuple_size_v<std::decay_t<Tuples>>...>;

    // ex:    tuple_size=3     tuple_size=2     tuple_size=4
    // list<    0, 1, 2,           0, 1,         0, 1, 2, 3   >
    using index_by_value = emp::join<
        emp::make_int_sequence<std::tuple_size<std::decay_t<Tuples>>>...
    >;

    return my_tuple_cat_impl<R>(index_by_tuple{}, index_by_value{},
        std::tuple<Tuples&&...>(std::forward<Tuples>(args)...));
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
static_assert(my_tuple == std_tuple{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
// @}

int main() {}
