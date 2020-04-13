#pragma once

#include "../functional/function.hpp"
#include "../utility/unpack.hpp"

#include <type_traits>

namespace jln::mp
{
  namespace detail
  {
    template<class Cmp, class C>
    struct mk_unique;
  }

  template<class C = listify>
  using unique = typename detail::mk_unique<cfe<std::is_same>, C>::type;

  template<class Cmp = cfe<std::is_same>, class C = listify>
  using unique_if = typename detail::mk_unique<Cmp, C>::type;

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = unpack<L, unique<C>>;

    template<class L, class Cmp = cfe<std::is_same>, class C = mp::listify>
    using unique_if = unpack<L, unique_if<Cmp, C>>;
  }
}


#include "same.hpp"
#include "fold_left.hpp"
#include "../list/pop_front.hpp"

#include <utility>

namespace jln::mp::detail
{
  template<class x>
  struct _inherit_impl {};
  template<std::size_t i, class x>
  struct inherit_impl : _inherit_impl<x> {};

  template<class, class...>
  struct inherit;

  template<std::size_t... ints, class... xs>
  struct inherit<std::integer_sequence<std::size_t, ints...>, xs...>
    : inherit_impl<ints, xs>...
  {};

#ifdef _MSC_VER
  template<class... xs>
  struct _is_set
  {
      template <class Pack>
      static auto is_set(Pack pack) -> decltype((
          static_cast<_inherit_impl<xs>*>(pack),...
      ), number<1>());

      static number<0> is_set(...);

      using type = decltype(is_set(static_cast<
        inherit<std::make_index_sequence<sizeof...(xs)>, xs...>*
      >(nullptr)));
  };
#endif

  template<class L, class x, class = void>
  struct _set_push_back
  {
    using type = L;
  };

  template<class... xs, class x>
  struct _set_push_back<list<xs...>, x,
    std::enable_if_t<
#ifdef _MSC_VER
      _is_set<xs..., x>::type::value
#else
      sizeof(inherit<std::make_index_sequence<sizeof...(xs)+1>, xs..., x>) == 1
#endif
  >>
  {
    using type = list<xs..., x>;
  };

  template<class> using to_false = std::false_type;

  struct _set_cmp_push_back_impl
  {
    template<class Cmp, class x, class... xs>
    using f = typename conditional_c<std::is_same<
      list<std::bool_constant<Cmp::template f<xs, x>::value>...>,
      list<to_false<xs>...>
    >::value>::template f<list<xs..., x>, list<xs...>>;
  };

  template<class Cmp>
  struct _set_cmp_push_back
  {
    template<class L, class x>
    using f = typename unpack<_set_cmp_push_back_impl>::template f<L, Cmp, x>;
  };

  template<class Cmp, class C>
  struct mk_unique
  {
    using type = push_front<list<>, fold_left<
      _set_cmp_push_back<Cmp>,
      unpack<C>
    >>;
  };

  template<class C>
  struct mk_unique<cfe<std::is_same>, C>
  {
    using type = push_front<list<>, fold_left<
      cfl<_set_push_back>,
      optimize_useless_unpack_t<unpack<C>>
    >>;
  };

  template<class C>
  struct mk_unique<cfl<std::is_same>, C>
  : mk_unique<cfe<std::is_same>, C>
  {};

  template<class C>
  struct mk_unique<same<>, C>
  : mk_unique<cfe<std::is_same>, C>
  {};
}
