#pragma once

#include "jln/mp/number/number.hpp"
#include "jln/mp/functional/is_invovable.hpp"

#define IS_INVOCABLE(...) jln::mp::true_{} = eager::is_invocable<__VA_ARGS__>{}
#define IS_INVOCABLE_V(...) [](auto _f, auto... _xs) { IS_INVOCABLE(decltype(_f), decltype(_xs)...); }(__VA_ARGS__)

namespace hack_test
{
  constexpr jln::mp::false_ operator !(jln::mp::true_ const&) { return {}; }
}

using hack_test::operator!;
