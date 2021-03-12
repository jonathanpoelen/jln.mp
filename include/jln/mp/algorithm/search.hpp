#pragma once

#include <jln/mp/algorithm/find.hpp>
#include <jln/mp/algorithm/index.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, bool found>
    struct _search;
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequence after a sub-\sequence.
  /// Calls \c TC with all the elements after the sub\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  template<class Pred, class TC = listify, class FC = clear<TC>>
  struct search
  {
    template<class... xs>
    using f = typename detail::find_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  /// Search the index of first sub-\sequence that satisfy a \predicate.
  /// \treturn \sequence
  template<class Pred, class TC = identity, class FC = size<>>
  struct search_index
  {
    template<class... xs>
    using f = typename detail::index_if_impl<
      typename detail::_search<
        detail::n_8_or_more_16_32_64_128_256(sizeof...(xs)), false
      >::template f<sizeof...(xs), Pred, xs...>
    >::template f<TC, FC, xs...>;
  };

  namespace emp
  {
    template<class L, class Pred, class TC = mp::listify, class FC = mp::clear<TC>>
    using search = unpack<L, mp::search<Pred, TC, FC>>;

    template<class L, class Pred, class TC = mp::identity, class FC = mp::size<>>
    using search_index = unpack<L, mp::search<Pred, TC, FC>>;
  }
}


/// \cond
namespace jln::mp::detail
{
#define JLN_DROP_WHILE_IMPL(n, m)                                     \
  template<>                                                          \
  struct _search<n, false>                                            \
  {                                                                   \
    template<std::size_t remaining, class Pred, class x, class... xs> \
    using f = typename _search<m, Pred::template f<x, xs...>::value>  \
            ::template f<remaining-1, Pred, xs...>;                   \
  };                                                                  \
                                                                      \
  template<>                                                          \
  struct _search<n, true>                                             \
  {                                                                   \
    template<std::size_t remaining, class Pred, class... xs>          \
    using f = _drop_while_result<sizeof...(xs)>;                      \
  }

  JLN_DROP_WHILE_IMPL(7, 6);
  JLN_DROP_WHILE_IMPL(6, 5);
  JLN_DROP_WHILE_IMPL(5, 4);
  JLN_DROP_WHILE_IMPL(4, 3);
  JLN_DROP_WHILE_IMPL(3, 2);
  JLN_DROP_WHILE_IMPL(2, 1);
  JLN_DROP_WHILE_IMPL(1, 0);

#undef JLN_DROP_WHILE_IMPL

  template<>
  struct _search<0, false>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_continue;
  };

  template<>
  struct _search<0, true>
  {
    template<std::size_t remaining, class Pred, class... xs>
    using f = _drop_while_result<sizeof...(xs)>;
  };

  template<>
  struct _search<8, false>
  {
    template<std::size_t remaining, class Pred, class x, class... xs>
    using f = typename _search<7, Pred::template f<x, xs...>::value>
      ::template f<remaining-8, Pred, xs...>;
  };

  template<>
  struct _search<16, false>
  {
    template<
      std::size_t remaining,
      class Pred,
      JLN_MP_XS_8(class, JLN_MP_NIL, JLN_MP_COMMA),
      class... xs>
    using f = typename _search<7, Pred::template f<
        JLN_MP_XS_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...
      >::value>
      ::template f<7, Pred,
                   JLN_MP_XS_2_TO_8(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA),
                   xs...>
      ::template f<_search<n_8_or_more_16_32_64_128_256(remaining-8), false>,
                   remaining-8, Pred, xs...>;
  };

#define JLN_DROP_WHILE_IMPL(n, m, xs)                                         \
  template<>                                                                  \
  struct _search<n, false>                                                    \
  {                                                                           \
    template<                                                                 \
      std::size_t remaining,                                                  \
      class Pred,                                                             \
      xs(class, JLN_MP_NIL, JLN_MP_COMMA),                                    \
      class... xs>                                                            \
    using f = typename _search<m, false>                                      \
      ::template f<m, Pred, xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), xs...>  \
      ::template f<_search<n_8_or_more_16_32_64_128_256(remaining-m), false>, \
                   remaining-m, Pred, xs...>;                                 \
  }

  JLN_DROP_WHILE_IMPL(32, 16, JLN_MP_XS_16);
  JLN_DROP_WHILE_IMPL(64, 32, JLN_MP_XS_32);
  JLN_DROP_WHILE_IMPL(128, 64, JLN_MP_XS_64);
  JLN_DROP_WHILE_IMPL(256, 128, JLN_MP_XS_128);

#undef JLN_DROP_WHILE_IMPL
}
/// \endcond
