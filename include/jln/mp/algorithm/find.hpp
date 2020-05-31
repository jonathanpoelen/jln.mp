#pragma once

#include "../list/listify.hpp"
#include "../utility/same_as.hpp"
#include "../utility/unpack.hpp"
#include "../functional/identity.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<int, unsigned>
    struct _find;

    constexpr unsigned _first_find_select(unsigned n);
  }
  /// \endcond

  /// \ingroup search

  /// Finds the first element that satisfy a predicate.
  /// Calls `FC` with all the elements since the one found at the end.
  /// If no element is found, `NFC` is used
  /// \treturn \sequence
  template<class Pred, class C = listify, class NC = C>
  struct find_if
  {
    template<class... xs>
    using f = typename detail::_find<-1,
      detail::_first_find_select(sizeof...(xs))
    >::template f<Pred, C, NC, xs...>;
  };

  template<class T, class C = listify, class NC = C>
  using find = find_if<same_as<T>, C, NC>;

  namespace emp
  {
    template<class L, class Pred, class C = mp::listify, class NC = C>
    using find_if = unpack<L, mp::find_if<Pred, C, NC>>;

    template<class L, class T, class C = mp::listify, class NC = C>
    using find = unpack<L, mp::find_if<mp::same_as<T>, C, NC>>;
  }
}


#include "../config/enumerate.hpp"
#include "../list/drop.hpp"

/// \cond
namespace jln::mp::detail
{
  constexpr unsigned _first_find_select(unsigned n)
  {
    return
      n == 0 ? 0
    : n < 64 ? 17
    : n < 256 ? 65
    : 257
    ;
  }

  template<int i, unsigned>
  struct _find
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename drop_c<i, C>::template f<xs...>;
  };

  template<>
  struct _find<-1, 0>
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename NC::template f<>;
  };

  template<bool... xs>
  constexpr int _index_of()
  {
    unsigned i = 0;
    (void)(... && (!xs && ++i));
    return i >= sizeof...(xs) ? -1 : int(i);
  }

#define JLN_MP_FIND_IMPL(nprev, mp_dup)                  \
  template<>                                             \
  struct _find<-1, nprev+16>                             \
  {                                                      \
    template<class Pred, class C, class NC,              \
      mp_dup(class, JLN_MP_COMMA),                       \
      class... xs>                                       \
    using f = typename _find<                            \
      _index_of<bool(Pred::template f<xs>::value)...>(), \
      0>                                                 \
    ::template f<Pred, C, NC, xs...>;                    \
  };

  JLN_MP_FIND_IMPL(0, JLN_MP_REPEAT_16)
  JLN_MP_FIND_IMPL(64, JLN_MP_REPEAT_64)
  JLN_MP_FIND_IMPL(256, JLN_MP_REPEAT_256)

#undef JLN_MP_FIND_IMPL

  template<>
  struct _find<-1, 17>
  {
    template<class Pred, class C, class NC, class... xs>
    using f = typename _find<
      _index_of<bool(Pred::template f<xs>::value)...>(),
      0>
    ::template f<Pred, C, NC, xs...>;
  };

  constexpr unsigned _find_select(unsigned n, unsigned r)
  {
    return
      n == 0 ? 0
    : (n < 64 ? 16
    : n < 256 ? 64
    : 256) + r
    ;
  }

#define JLN_MP_FIND_IMPL(nprev, n, mp_skip, mp_xs) \
  template<>                                       \
  struct _find<-1, nprev+n>                        \
  {                                                \
    template<class Pred, class C, class NC,        \
      mp_skip(class, JLN_MP_COMMA),                \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),      \
      class... xs>                                 \
    using f = typename _find<                      \
      _index_of<mp_xs(                             \
        bool JLN_MP_PAREN_OPEN Pred::template f<,  \
        >::value JLN_MP_PAREN_CLOSE, JLN_MP_COMMA  \
      )>(),                                        \
      _find_select(sizeof...(xs), n)               \
    >                                              \
    ::template f<                                  \
      Pred, C, NC,                                 \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), \
      xs...                                        \
    >;                                             \
  };

  JLN_MP_FIND_IMPL(64, 64, JLN_MP_REPEAT_64, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, 64, JLN_MP_REPEAT_256, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, 256, JLN_MP_REPEAT_256, JLN_MP_XS_256)

#undef JLN_MP_FIND_IMPL

#define JLN_MP_FIND_IMPL(n, mp_xs)                 \
  template<>                                       \
  struct _find<-1, n+1>                            \
  {                                                \
    template<class Pred, class C, class NC,        \
      mp_xs(class, JLN_MP_NIL, JLN_MP_COMMA),      \
      class... xs>                                 \
    using f = typename _find<                      \
      _index_of<mp_xs(                             \
        bool JLN_MP_PAREN_OPEN Pred::template f<,  \
        >::value JLN_MP_PAREN_CLOSE, JLN_MP_COMMA  \
      )>(),                                        \
      _find_select(sizeof...(xs), n)>              \
    ::template f<                                  \
      Pred, C, NC,                                 \
      mp_xs(JLN_MP_NIL, JLN_MP_NIL, JLN_MP_COMMA), \
      xs...>;                                      \
  };

  JLN_MP_FIND_IMPL(64, JLN_MP_XS_64)
  JLN_MP_FIND_IMPL(256, JLN_MP_XS_256)

#undef JLN_MP_FIND_IMPL
}
/// \endcond
