#pragma once

#include "../list/list.hpp"
#include "../utility/unpack.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int>
    struct _intersperse;
  }
  /// \endcond

  /// \ingroup algorithm

  /// Insert a \value between each element of a \sequence.
  /// \treturn \list
  template<class x, class C = listify>
  struct intersperse
  {
    template<class... xs>
    using f = typename detail::_intersperse<sizeof...(xs) ? 1 : 0>
      ::template f<C, x, xs...>;
  };

  namespace emp
  {
    template<class L, class x, class C = mp::listify>
    using intersperse = unpack<L, mp::intersperse<x, C>>;
  }
}


#include "zip.hpp"
#include "make_int_sequence.hpp"
#include "transform.hpp"
#include "../list/join.hpp"
#include "../list/pop_front.hpp"
#include "../utility/always.hpp"

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _intersperse<0>
  {
    template<class C, class x>
    using f = typename C::template f<>;
  };

  template<>
  struct _intersperse<1>
  {
    template<class C, class x, class... xs>
    using f = typename _zip_impl<
      join<pop_front<C>>,
      emp::make_int_sequence_c<sizeof...(xs), transform<always<x>>>,
      list<xs...>
    >::type;
  };
}
/// \endcond
