#pragma once

#include "list.hpp"

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<class Pred>
    struct mk_wrap_in_list_if;

    template<class Pred>
    struct mk_wrap_in_list_if_not;
  }
  /// \endcond

  /// \ingroup list

  /// Returns a \list with the first element if the predicate is checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if = typename detail::mk_wrap_in_list_if<Pred>::type;

  /// Returns a \list with the first element if the predicate is not checked, otherwise returns a empty list.
  /// \pre \c Pred<xs...>::value must be narrowing convertible to bool
  /// \treturn \list
  template<class Pred>
  using wrap_in_list_if_not = typename detail::mk_wrap_in_list_if_not<Pred>::type;

  template<bool b>
  struct wrap_in_list_c;

  template<>
  struct wrap_in_list_c<true>
  {
    template<class... xs>
    using f = list<xs...>;
  };

  template<>
  struct wrap_in_list_c<false>
  {
    template<class>
    using f = list<>;
  };

  template<class b>
  using wrap_in_list = wrap_in_list_c<b::value>;

  namespace emp
  {
    template<class Pred, class... xs>
    using wrap_in_list_if = typename mp::wrap_in_list_if<Pred>::template f<xs...>;

    template<class Pred, class... xs>
    using wrap_in_list_if_not = typename mp::wrap_in_list_if_not<Pred>::template f<xs...>;

    template<class b, class... xs>
    using wrap_in_list = typename mp::wrap_in_list_c<b::value>::template f<xs...>;

    template<bool b, class... xs>
    using wrap_in_list_c = typename mp::wrap_in_list_c<b>::template f<xs...>;
  }
}

#include "../algorithm/same.hpp"
#include "../utility/same_as.hpp"
#include "../functional/call.hpp"
#include "../functional/tee.hpp"
#include "../number/operators.hpp"

/// \cond
namespace jln::mp::detail
{
  template<class Pred>
  struct _wrap_in_list_if
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if
  {
    using type = _wrap_in_list_if<Pred>;
  };

  template<class x, class C>
  struct mk_wrap_in_list_if<same_as<x, not_<C>>>
  : mk_wrap_in_list_if_not<same_as<x, C>>
  {};

  template<class C>
  struct mk_wrap_in_list_if<same<not_<C>>>
  : mk_wrap_in_list_if_not<same<C>>
  {};

  template<class C>
  struct mk_wrap_in_list_if<not_<C>>
  : mk_wrap_in_list_if_not<C>
  {};

  template<class Pred>
  struct mk_wrap_in_list_if<tee<Pred, not_<>>>
  : mk_wrap_in_list_if_not<Pred>
  {};


  template<class Pred>
  struct _wrap_in_list_if_not
  {
    template<class x, class... xs>
    using f = typename wrap_in_list_c<!call<Pred, x, xs...>::value>::template f<x>;
  };

  template<class Pred>
  struct mk_wrap_in_list_if_not
  {
    using type = _wrap_in_list_if_not<Pred>;
  };

  template<class x, class C>
  struct mk_wrap_in_list_if_not<same_as<x, not_<C>>>
  : mk_wrap_in_list_if<same_as<x, C>>
  {};

  template<class C>
  struct mk_wrap_in_list_if_not<same<not_<C>>>
  : mk_wrap_in_list_if<same<C>>
  {};

  template<class C>
  struct mk_wrap_in_list_if_not<not_<C>>
  : mk_wrap_in_list_if<C>
  {};

  template<class Pred>
  struct mk_wrap_in_list_if_not<tee<Pred, not_<>>>
  : mk_wrap_in_list_if<Pred>
  {};
}
/// \endcond
