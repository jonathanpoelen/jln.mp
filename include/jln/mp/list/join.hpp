#pragma once

#include "listify.hpp"
#include "../functional/call.hpp"
#include "../error.hpp"
#include "../config/debug.hpp"

#include <cstddef>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n JLN_MP_DEBUG_A(class = err::all_parameters_must_be_of_type_mp_list)>
    struct _join_select;
  }
  /// \endcond

  /// \ingroup list

  /// Concatenates \lists.
  /// \pre \c seqs must be a \sequence of \list
  /// \treturn \sequence
  template<class C = listify>
  struct join
  {
    template<class... seqs>
    using f = typename detail::_join_select<sizeof...(seqs)>::template f<C, seqs...>::type;
  };

  namespace emp
  {
    template<class... seqs>
    using join = mp::call<mp::join<>, seqs...>;
  }
}

#include "../config/enumerate.hpp"
#include "../../cxx/diagnostic.hpp"

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n JLN_MP_DEBUG_A(class error)>
  struct _join_select : _join_select<n_16_64_256_1024(n)>
  {};

  JLN_DIAGNOSTIC_PUSH
  JLN_DIAGNOSTIC_MSVC_IGNORE(4348)

#define JLN_MP_JOIN_SELECT(n, mp_xs, mp_rxs, _)   \
  template<JLN_MP_DEBUG(class error)>             \
  struct _join_select<n JLN_MP_DEBUG_A(error)>    \
  {                                               \
    template<class F,                             \
      mp_xs(class, = list<>, JLN_MP_COMMA)>       \
    struct f;                                     \
                                                  \
    template<class F,                             \
      mp_xs(class..., JLN_MP_NIL, JLN_MP_COMMA)>  \
    struct f<F, mp_xs(list<, ...>, JLN_MP_COMMA)> \
    {                                             \
      using type = typename F::template f<        \
        mp_xs(JLN_MP_NIL, ..., JLN_MP_COMMA)>;    \
    };                                            \
  };

  JLN_MP_GEN_XS_16_64_256(JLN_MP_JOIN_SELECT)

#undef JLN_MP_JOIN_SELECT

  template<JLN_MP_DEBUG(class error)>
  struct _join_select<1024 JLN_MP_DEBUG_A(error)>
  {
    template<class F,
      JLN_MP_XS_1024(class, = list<>, JLN_MP_COMMA),
      class... tail>
    struct f;

    template<class F,
      JLN_MP_XS_1024(class..., JLN_MP_NIL, JLN_MP_COMMA),
      class... tail>
    struct f<F, JLN_MP_XS_1024(list<, ...>, JLN_MP_COMMA), tail...>
    : _join_select<sizeof...(tail)+1>
    ::template f<F, list<JLN_MP_XS_1024(JLN_MP_NIL, ..., JLN_MP_COMMA)>, tail...>
    {};
  };

  JLN_DIAGNOSTIC_POP

} // namespace jln::mp::detail
/// \endcond
