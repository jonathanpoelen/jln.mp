// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/smp/functional/identity.hpp>
#include <jln/mp/smp/algorithm/any_of.hpp>
#include <jln/mp/smp/utility/is.hpp>
#include <jln/mp/algorithm/contains.hpp>

namespace jln::mp::smp
{
  template<class x, class C = identity>
  using contains = contract<mp::any_of<mp::is<x>, assume_positive_number<C>>>;
}
