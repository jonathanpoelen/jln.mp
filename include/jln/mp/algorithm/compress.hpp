#pragma once

#include <jln/mp/list/clear.hpp>
#include <jln/mp/list/join.hpp>
#include <jln/mp/number/number.hpp>
#include <jln/mp/functional/each.hpp>
#include <jln/mp/utility/conditional.hpp>

namespace jln::mp
{
  /// \ingroup algorithm

  /// Removes elements that have a corresponding element in selectors to 0.
  /// \pre `emp::unpack<Selectors, listify> == Selectors`
  /// \pre all Selectors::value are 1, 0 or a bool type
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   call<compress<numbers<1,0,1,0,1,1>,
  ///     a,b,c,d,e,f
  ///   > = list<
  ///     a,  c,  e,f
  ///   >
  ///   \endconde
  /// \treturn \sequence
  template<class Selectors, class C = listify>
  struct compress
  {};

#ifdef JLN_MP_DOXYGENATING
  template<class... selectors, class C = listify>
  struct compress<list<selectors...>, C>
  {
    template<class... xs>
    using f;
  };
#endif

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = unpack<L, mp::compress<Selectors, C>>;

    template<class L, bool... selectors>
    using compress_with_c = unpack<L, mp::compress<list<number<selectors>...>>>;
  }

  /// \cond
  template<class... selectors, class C>
  struct compress<list<selectors...>, C>
  : each<typename conditional_c<selectors::value>::template f<listify, clear<>>..., join<C>>
  {};
  /// \endcond
}
