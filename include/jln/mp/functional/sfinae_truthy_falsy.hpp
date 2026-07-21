// SPDX-FileCopyrightText: 2026 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/detail/compiler.hpp>
#include <jln/mp/functional/identity.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{

  /// \ingroup algorithm

#if JLN_MP_FEATURE_CONCEPTS

  /// The concept is satisfied if and only if \c Pred::f<xs...> is truthy.
  /// Due to the very nature of how these concepts work, this may return `false`
  /// rather than a compilation error with an SFINAE failure. This is the case,
  /// for example, with `sfinae_truthy_as<greater<>>::f<void, void>`.
  template<class Pred, class... xs>
  concept sfinae_truthy_as = !!Pred::template f<xs...>::value;

  /// The concept is satisfied if and only if \c Pred::f<xs...> is falsy.
  /// Due to the very nature of how these concepts work, this may return `false`
  /// rather than a compilation error with an SFINAE failure. This is the case,
  /// for example, with `sfinae_falsy_as<greater<>>::f<void, void>`.
  template<class Pred, class... xs>
  concept sfinae_falsy_as = !Pred::template f<xs...>::value;


  /// Checks the \c sfinae_truthy_as concept.
  /// \treturn \bool
  /// \see sfinae_truthy_as, sfinae_falsy_as, is_sfinae_falsy
  template<class Pred, class C = identity>
  struct is_sfinae_truthy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sfinae_truthy_as<Pred, xs...>>);
  };

  /// Checks the \c sfinae_falsy_as concept.
  /// \treturn \bool
  /// \see sfinae_truthy_as, sfinae_falsy_as, is_sfinae_truthy
  template<class Pred, class C = identity>
  struct is_sfinae_falsy
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(C, number<sfinae_falsy_as<Pred, xs...>>);
  };

  namespace emp
  {
    template<class L, class Pred, class C = mp::identity>
    using is_sfinae_truthy = typename detail::_unpack<mp::is_sfinae_truthy<Pred, C>, L>::type;

    template<class L, class Pred, class C = mp::identity>
    using is_sfinae_falsy = typename detail::_unpack<mp::is_sfinae_falsy<Pred, C>, L>::type;
  }

#endif

} // namespace jln::mp

#if JLN_MP_FEATURE_CONCEPTS
/// \cond
namespace jln::mp
{
  template<class Pred>
  struct is_sfinae_truthy<Pred>
  {
    template<class... xs>
    using f = number<sfinae_truthy_as<Pred, xs...>>;
  };

  template<class Pred>
  struct is_sfinae_falsy<Pred>
  {
    template<class... xs>
    using f = number<sfinae_falsy_as<Pred, xs...>>;
  };
}
/// \endcond
#endif
