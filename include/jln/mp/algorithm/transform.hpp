#pragma once

#include "../list/listify.hpp"
#include "../utility/unpack.hpp"
#include "../functional/call.hpp"


namespace jln::mp
{
  /// \ingroup algorithm

  /// Executes \c F on every element of a \sequence.
  /// \treturn \sequence
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = dispatch<C, F, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = unpack<L, mp::transform<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
/// \endcond
