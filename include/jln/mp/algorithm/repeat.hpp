#pragma once

#include <jln/mp/algorithm/make_int_sequence.hpp>
#include <jln/mp/utility/unpack.hpp>
#include <jln/mp/detail/enumerate.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int_ n>
    struct _repeat;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Returns a \sequence that contains a \number of copies of the same \sequence.
  /// \pre N >= 0
  /// \treturn \sequence
  template<unsigned N, class C = listify>
  struct repeat_c
  {
    template<class... xs>
    using f = emp::make_int_sequence_c<N,
      typename detail::_repeat<detail::min(sizeof...(xs), 2)>
        ::template f<C, xs...>>;
  };

  template<class N, class C = listify>
  using repeat = repeat_c<N::value, C>;

  namespace emp
  {
    template<class L, class n, class C = mp::listify>
    using repeat = unpack<L, mp::repeat<n, C>>;

    template<class L, int_ n, class C = mp::listify>
    using repeat_c = unpack<L, mp::repeat_c<n, C>>;
  }
}


#include <jln/mp/algorithm/transform.hpp>
#include <jln/mp/algorithm/cartesian.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/utility/always.hpp>

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _repeat<0>
  {
    template<class C>
    using f = _cartesian<C, 0>; // for C::f<>
  };

  template<>
  struct _repeat<1>
  {
    template<class C, class x>
    using f = transform<always<x>, C>;
  };

  template<>
  struct _repeat<2>
  {
    template<class C, class... xs>
    using f = transform<always<list<xs...>>, join<C>>;
  };
}
/// \endcond
