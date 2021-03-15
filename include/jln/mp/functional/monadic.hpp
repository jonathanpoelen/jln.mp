#pragma once

#include <jln/mp/functional/try.hpp>
#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/number/operators.hpp>
#include <jln/mp/list/front.hpp>

#include <type_traits>


namespace jln::mp
{
  /// \ingroup functional

  /// Invokes \c FC whether `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic = if_<is<na>, FC, C>;

  /// Invokes \c FC whether first value is `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic0 = if_<front<is<na>>, FC, C>;

  /// Invokes \c FC whether any value is `na`, otherwise \c C.
  /// \treturn \value
  template<class C, class FC = violation>
  using monadic_xs = if_<transform<is<na>, or_<>>, FC, C>;

  /// Monadify only if \c x is \c na.
  /// \treturn \value
  template<class x, template<class...> class M, class C, class FC = violation>
  using monadic_if_na = typename conditional_c<std::is_same<na, x>::value>
    ::template f<M<C, FC>, C>;
}
