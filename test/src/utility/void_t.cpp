// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#include "test/test_case.hpp"

#include "jln/mp/utility/void_t.hpp"
#include "jln/mp/algorithm/same.hpp"

TEST_SUITE_BEGIN()

static_assert(jln::mp::emp::same_xs_v<void, jln::mp::void_t<>>);
static_assert(jln::mp::emp::same_xs_v<void, jln::mp::void_t<int>>);
static_assert(jln::mp::emp::same_xs_v<void, jln::mp::void_t<int, int>>);

TEST_SUITE_END()
