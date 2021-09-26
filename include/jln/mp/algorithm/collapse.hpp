#pragma once

#include <jln/mp/algorithm/group.hpp>

namespace jln::mp
{
  /// \ingroup group

  /// Groups adjacent elements by adjacent keys.
  /// \semantics
  /// \pre `emp::is_list<Keys>` == `true`
  /// \pre `emp::size<Keys>` == `sizeof...(xs)`
  ///   \code
  ///   call<collapse<emp::numbers<1, 1, 0, 0, 0, 1, 2, 2>>,
  ///     int, int, int, int, int, int, int, int
  ///   > = list<
  ///     list<int, int>,
  ///     list<int, int, int>,
  ///     list<int>,
  ///     list<int, int>
  ///   >
  ///   \endcode
  /// \note \c collapse<list<xs...>>::f<xs...> == \c group<>::f<xs...>
  /// \treturn \sequence
  template<class Keys, class C = listify>
  struct collapse
  {};

#ifdef JLN_MP_DOXYGENATING
  template<class... keys, class C>
  struct collapse<list<keys...>, C>
  {
    template<class... xs>
    using f;
  };
#endif

  namespace emp
  {
    template<class L, class Keys, class C = mp::listify>
    using collapse = unpack<L, mp::collapse<Keys, C>>;
  }


  /// \cond
  namespace detail
  {
    template<class...>
    struct make_collapse;
  }

  template<class C>
  struct collapse<list<>, C>
  {
    template<class... xs>
    using f = typename detail::_group<sizeof...(xs) != 0>
      ::template f<C, list<>>;
  };

  template<class key, class... keys, class C>
  struct collapse<list<key, keys...>, C>
  : detail::make_collapse<
      typename take_front_c<sizeof...(keys)>::template f<key, keys...>,
      keys...
    >::template f<C>
  {};
  /// \endcond
}


namespace jln::mp::detail
{
  template<class C, class... ns>
  struct _collapse
  {
    template<class x, class... xs>
    using f = typename fold_right<lift_t<split_state>, unpack<_group_insert_x<x, C>>>
      ::template f<list<list<>>, list<ns, xs>...>;
  };

  template<class... xs, class... ys>
  struct make_collapse<list<ys...>, xs...>
  {
    template<class C>
    using f = _collapse<
      C, number<std::is_same<ys, xs>::value ? split_keep : split_before>...
    >;
  };
}