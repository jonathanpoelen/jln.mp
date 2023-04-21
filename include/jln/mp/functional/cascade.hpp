#pragma once

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class, class...>
    struct _cascade;
  }
  /// \endcond

  /// \ingroup functional

  /// Recursively invokes \functions to nested \typelist of \typelists.
  /// \semantics
  ///   \code
  ///     cascade<F0> = transform<F0>
  ///     cascade<F0,F1,F2> = transform<unpack<transform<unpack<F0>, F1>>, F2>
  ///   \endcode
  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}


#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/utility/unpack.hpp>

/// \cond
namespace jln::mp::detail
{
  template<class F0, class F1, class... Fs>
  struct _cascade<F0, F1, Fs...>
    : _cascade<transform<unpack<F0>, F1>, Fs...>
  {};

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F0>, F1>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
/// \endcond
