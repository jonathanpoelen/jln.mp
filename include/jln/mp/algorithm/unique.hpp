#include "fold_left.hpp"
#include "../functional/bind.hpp"
#include "../utility/eager.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class L, class x, class = void>
    struct _set_push_back2;
  }

  template<class C = listify>
  struct unique
  {
    template<class... xs>
    // TODO unpack<listify> -> identity
    using f = typename fold_left<cfl<detail::_set_push_back2>, unpack<C>>
      ::template f<list<>, xs...>;
  };

  namespace emp
  {
    template<class L, class C = mp::listify>
    using unique = eager<L, unique<C>>;
  }
}


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

  template<class L, class x, class>
  struct _set_push_back2
  {
    using type = L;
  };

  template<class... xs, class x>
  struct _set_push_back2<list<xs...>, x,
  // TODO contains
    std::enable_if_t<sizeof(inherit<std::make_index_sequence<sizeof...(xs)+1>, xs..., x>) == 1>>
  {
    using type = list<xs..., x>;
  };
}
