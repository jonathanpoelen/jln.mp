#pragma once

#include <jln/mp/algorithm/starts_with.hpp>
#include <jln/mp/algorithm/index.hpp>
#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/functional/tee.hpp>
#include <jln/mp/functional/invoke_twice.hpp>

namespace jln::mp
{
  /// \cond
  namespace detail
  {
    template<std::size_t n, class SubC1, class SubC2, class C>
    struct before_after_defer_i;
  }
  /// \endcond

  /// \ingroup search

  /// Find the \sequence before_after a sub-\sequence.
  /// Calls \c TC with all the elements before_after the sub-\sequence found.
  /// If no element is found, \c FC is used with the whole \sequence.
  /// \treturn \sequence
  /// \see search, search_before
  template<
    class Seq,
    class SubC1 = listify, class SubC2 = SubC1,
    class TC = listify, class FC = clear<TC>>
  struct before_after_with
  {};

  template<class Seq, class TC = listify, class FC = clear<TC>>
  using before_after = before_after_with<Seq, listify, listify, TC, FC>;

  template<class... Ts, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<Ts...>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if_xs<starts_with<list<Ts...>>,
                             detail::before_after_defer_i<sizeof...(Ts), SubC1, SubC2, TC>,
                             mp::always<FC>>>
  {};

  namespace emp
  {
    template<class L, class Seq, class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after = unpack<L, mp::before_after<Seq, TC, FC>>;

    template<class L, class Seq,
             class SubC1 = mp::listify, class SubC2 = SubC1,
             class TC = mp::listify, class FC = mp::clear<TC>>
    using before_after_with = unpack<L, mp::before_after_with<Seq, SubC1, SubC2, TC, FC>>;
  }

  /// \cond
  template<class T, class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<T>, SubC1, SubC2, TC, FC>
  : invoke_twice<index_if<is<T>,
                          detail::before_after_defer_i<1, SubC1, SubC2, TC>,
                          mp::always<FC>>>
  {};

  template<class SubC1, class SubC2, class TC, class FC>
  struct before_after_with<list<>, SubC1, SubC2, TC, FC>
  {
    template<class... xs>
    using f = JLN_MP_CALL_TRACE(TC,
      JLN_MP_DCALL_TRACE_XS_0(xs, SubC1),
      JLN_MP_DCALL_TRACE_XS(xs, SubC2, xs...)
    );
  };
  /// \endcond
}

/// \cond
namespace jln::mp::detail
{
  template<std::size_t n, class SubC1, class SubC2, class C>
  struct before_after_defer_i
  {
    template<class I>
    using f = tee<take_front<I, SubC1>, drop_front_c<I::value + n, SubC2>, C>;
  };
}
/// \endcond
