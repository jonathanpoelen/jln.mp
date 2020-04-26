#pragma once

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred>
    struct mk_list_wrap_if;

    template<class Pred>
    struct mk_list_wrap_if_not;

    template<bool>
    struct _list_wrap_if_c;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a \list with the first element if the predicate is checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using list_wrap_if = typename detail::mk_list_wrap_if<Pred>::type;

  /// Returns a \list with the first element if the predicate is not checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using list_wrap_if_not = typename detail::mk_list_wrap_if_not<Pred>::type;

  template<bool b>
  using list_wrap_if_c = detail::_list_wrap_if_c<b>;

  namespace emp
  {
    template<class Pred, class... xs>
    using list_wrap_if = typename mp::list_wrap_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using list_wrap_if_not = typename mp::list_wrap_if_not<Pred>::template f<xs...>;

    template<bool b, class... xs>
    using list_wrap_if_c = typename mp::list_wrap_if_c<b>::template f<xs...>;
  }
}

#include "list.hpp"
#include "../algorithm/same.hpp"
#include "../utility/same_as.hpp"
#include "../functional/call.hpp"
#include "../functional/fork.hpp"
#include "../number/operators.hpp"

/// \cond
namespace jln::mp::detail
{
  template<>
  struct _list_wrap_if_c<false>
  {
    template<class>
    using f = list<>;
  };

  template<>
  struct _list_wrap_if_c<true>
  {
    template<class x>
    using f = list<x>;
  };


  template<class Pred>
  struct _list_wrap_if
  {
    template<class x, class... xs>
    using f = typename _list_wrap_if_c<call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_list_wrap_if
  {
    using type = _list_wrap_if<Pred>;
  };

  template<class x, class C>
  struct mk_list_wrap_if<same_as<x, not_<C>>>
  : mk_list_wrap_if_not<same_as<x, C>>
  {};

  template<class C>
  struct mk_list_wrap_if<same<not_<C>>>
  : mk_list_wrap_if_not<same<C>>
  {};

  template<class C>
  struct mk_list_wrap_if<not_<C>>
  : mk_list_wrap_if_not<C>
  {};

  template<class Pred>
  struct mk_list_wrap_if<fork<Pred, not_<>>>
  : mk_list_wrap_if_not<Pred>
  {};


  template<class Pred>
  struct _list_wrap_if_not
  {
    template<class x, class... xs>
    using f = typename _list_wrap_if_c<!call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_list_wrap_if_not
  {
    using type = _list_wrap_if_not<Pred>;
  };

  template<class x, class C>
  struct mk_list_wrap_if_not<same_as<x, not_<C>>>
  : mk_list_wrap_if<same_as<x, C>>
  {};

  template<class C>
  struct mk_list_wrap_if_not<same<not_<C>>>
  : mk_list_wrap_if<same<C>>
  {};

  template<class C>
  struct mk_list_wrap_if_not<not_<C>>
  : mk_list_wrap_if<C>
  {};

  template<class Pred>
  struct mk_list_wrap_if_not<fork<Pred, not_<>>>
  : mk_list_wrap_if<Pred>
  {};
}
/// \endcond
