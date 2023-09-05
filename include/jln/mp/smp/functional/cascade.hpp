// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/algorithm/transform.hpp>
#include <jln/mp/smp/utility/unpack.hpp>
#include <jln/mp/functional/cascade.hpp>

namespace jln::mp::smp
{
  template<class F, class... Fs>
  using cascade = typename detail::sfinae<mp::cascade<
    subcontract_barrier<F>,
    subcontract_barrier<Fs>...
  >>;
}
