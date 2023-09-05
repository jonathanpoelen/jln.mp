// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include "jln/mp/value/values.hpp"
#include "jln/mp/number/number.hpp"

namespace ut
{
namespace
{
  namespace ints
  {
    struct bad_val {};

    using v0 = jln::mp::typed_val<jln::mp::int_, 0>;
    using v1 = jln::mp::typed_val<jln::mp::int_, 1>;
    using v2 = jln::mp::typed_val<jln::mp::int_, 2>;

    using vseq_0 = jln::mp::emp::typed_values<jln::mp::int_, 0>;
    using vseq_0_1_2 = jln::mp::emp::typed_values<jln::mp::int_, 0, 1, 2>;
  }
}
}
