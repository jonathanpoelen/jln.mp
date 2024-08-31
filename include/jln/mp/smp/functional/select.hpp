// SPDX-FileCopyrightText: 2024 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/if.hpp>
#include <jln/mp/functional/select.hpp>

namespace jln::mp::smp
{
  template<class Pred, class TC = identity, class FC = TC>
  using select = detail::smp_select_impl<
    1, assume_binary_or_more<Pred>,
    mp::front<assume_unary<TC>>,
    mp::at1<assume_unary<FC>>
  >;

  template<class Pred, class TC = identity, class FC = TC>
  using reverse_select = detail::smp_select_impl<
    1, assume_binary_or_more<Pred>,
    mp::at1<assume_unary<TC>>,
    mp::front<assume_unary<FC>>
  >;
}
