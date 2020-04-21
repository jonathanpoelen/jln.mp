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

  /// \ingroup list

  /// Recursively applies \functions to nested \typelist of \typelists.
  /// \semantics:
  ///   \code
  ///     cascade<F0,F1,F2> = transform<unpack<transform<unpack<F2>, F1>>, F0>
  ///   \endcode
  template<class F, class... Fs>
  using cascade = typename detail::_cascade<F, Fs...>::type;
}


#include "../algorithm/transform.hpp"
#include "../utility/unpack.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class F, class... Fs>
  struct _cascade
  {
    using type = transform<unpack<typename _cascade<Fs...>::type>, F>;
  };

  template<class F0, class F1>
  struct _cascade<F0, F1>
  {
    using type = transform<unpack<F1>, F0>;
  };

  template<class F>
  struct _cascade<F>
  {
    using type = transform<F>;
  };
}
/// \endcond
