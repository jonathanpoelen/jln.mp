#pragma once

#include <jln/mp/list/join.hpp>
#include <jln/mp/list/wrap_in_list.hpp>
#include <jln/mp/number/number.hpp>

namespace jln::mp
{
  /// \ingroup filter

  /// Removes elements that have a corresponding element in selectors to 0.
  /// \pre `emp::unpack<Selectors, listify> == Selectors`
  /// \pre all `Selectors::value` are `1`, `0` or a `bool` value
  /// \pre `sizeof...(xs) == emp::size<Selectors>`
  /// \semantics
  ///   \code
  ///   compress<numbers<1,0,1,0,1,1>>
  ///                ::f<a,b,c,d,e,f>
  ///            == list<a,  c,  e,f>
  ///   \endcode
  /// \treturn \sequence
  template<class Selectors, class C = listify>
  struct compress
  {};

  template<class... selectors, class C>
  struct compress<list<selectors...>, C>
  {
    template<class... xs>
    using f = typename join<C>::template f<
      JLN_MP_MSVC_FIX_CALL_T((wrap_in_list_c<selectors::value>), xs)...
    >;
  };

  template<class... Selectors>
  using compress_for = compress<list<Selectors...>>;

  template<bool... selectors>
  using compress_for_c = compress<list<number<selectors>...>>;

  namespace emp
  {
    template<class L, class Selectors, class C = mp::listify>
    using compress = unpack<L, mp::compress<Selectors, C>>;

    template<class L, class... Selectors>
    using compress_for = unpack<L, mp::compress<mp::list<Selectors...>>>;

    template<class L, bool... selectors>
    using compress_for_c = unpack<L, mp::compress<mp::list<number<selectors>...>>>;
  }
}
