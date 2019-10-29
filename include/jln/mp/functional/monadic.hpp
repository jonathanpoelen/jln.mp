#pragma once

#include "../algorithm/transform.hpp"
#include "../number/operators.hpp"
#include "../list/front.hpp"


namespace jln::mp
{
  template<class C, class FC = violation>
  using monadic = if_<same_as<na>, FC, C>;

  template<class C, class FC = violation>
  using monadic0 = if_<front<same_as<na>>, FC, C>;

  template<class C, class FC = violation>
  using monadic_xs = if_<transform<same_as<na>, or_<>>, FC, C>;
}
