#pragma once

#include <jln/mp/list/sliding.hpp>
#include <jln/mp/utility/conditional.hpp>
#include <jln/mp/list/clear.hpp>


namespace jln::mp
{
  /// \ingroup group

  /// Returns successive overlapping pairs.
  /// \post If `sizeof...(xs) < 2`, then the result sequence is empty
  /// \post If `sizeof...(xs) >= 2`, then the number of 2-tuples is `sizeof...(xs) - 1`
  /// \semantics
  ///   \code
  ///   call<pairwise<>>,
  ///     a, b, c, d
  ///   > = list<
  ///     list<a, b>,
  ///     list<b, c>,
  ///     list<c, d>
  ///   >
  ///   \endcode
  /// \treturn \sequence of \list
  /// \see sliding, group_n
#ifdef JLN_MP_DOXYGENATING
  template<class C = listify>
  using pairwise = if_<size<less_than<2>>, clear<C>, sliding_c<2, C>>;
#else
  template<class C = listify>
  struct pairwise
  {
    template<class... xs>
    using f = typename conditional_c<(sizeof...(xs) < 2)>
      ::template f<clear<C>, sliding_c<2, C>>::template f<xs...>;
  };
#endif

  namespace emp
  {
    template<class L, class C = mp::listify>
    using pairwise = unpack<L, mp::pairwise<C>>;
  }
}
