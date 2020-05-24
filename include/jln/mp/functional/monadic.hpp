#pragma once

#include "../functional/try.hpp"
#include "../algorithm/transform.hpp"
#include "../number/operators.hpp"
#include "../list/front.hpp"

#include <type_traits>


namespace jln::mp
{
  /// \ingroup functional

  /// Call another \function if the value is `na`.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic = if_<same_as<na>, FC, C>;

  /// Call another \function if the first value is `na`.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic0 = if_<front<same_as<na>>, FC, C>;

  /// Call another \function if there is at least some `na` value.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic_xs = if_<transform<same_as<na>, or_<>>, FC, C>;

  /// Monadify only if `x` is `na`.
  /// \treturn \value
  template<class x, template<class...> class M, class C, class FC = violation>
  using monadic_if_na = typename conditional_c<std::is_same<na, x>::value>
    ::template f<M<C, FC>, C>;
}
