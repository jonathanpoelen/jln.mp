// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include <jln/mp/list/drop_front.hpp>
#include <jln/mp/list/front.hpp>

namespace jln::mp
{
  /// \ingroup list

#if !JLN_MP_HAS_BUILTIN(__type_pack_element)
# define JLN_MP_AT_C(i, ...) ::jln::mp::at_c<i>::template f<__VA_ARGS__>
# define JLN_MP_AT_CC(i, ...) ::jln::mp::at_c<i>::f<__VA_ARGS__>
# define JLN_MP_AT_C_T(i, ...) typename ::jln::mp::at_c<i>::template f<__VA_ARGS__>
# define JLN_MP_AT_CC_T(i, ...) typename ::jln::mp::at_c<i>::f<__VA_ARGS__>
#else
# define JLN_MP_AT_C(i, ...) __type_pack_element<i, __VA_ARGS__>
# define JLN_MP_AT_CC(i, ...) __type_pack_element<i, __VA_ARGS__>
# define JLN_MP_AT_C_T(i, ...) __type_pack_element<i, __VA_ARGS__>
# define JLN_MP_AT_CC_T(i, ...) __type_pack_element<i, __VA_ARGS__>
#endif

  /// Retrieves an element of a sequence at an arbitrary position.
  /// \pre `0 <= N < sizeof...(xs)`
  /// \treturn \value
  template<class N, class C = identity>
  using at = drop_front<N, front<C>>;

  template<unsigned n, class C = identity>
  using at_c = drop_front_c<n, front<C>>;

  template<class C = identity>
  using at0 = front<C>;

  template<class C = identity>
  using at1 = drop_front_c<1, front<C>>;

  template<class C = identity>
  using at2 = drop_front_c<2, front<C>>;

  template<class C = identity>
  using at3 = drop_front_c<3, front<C>>;

  template<class C = identity>
  using at4 = drop_front_c<4, front<C>>;

  template<class C = identity>
  using at5 = drop_front_c<5, front<C>>;

  template<class C = identity>
  using at6 = drop_front_c<6, front<C>>;

  template<class C = identity>
  using at7 = drop_front_c<7, front<C>>;

  template<class C = identity>
  using at8 = drop_front_c<8, front<C>>;

  template<class C = identity>
  using at9 = drop_front_c<9, front<C>>;

  namespace emp
  {
    template<class L, class i, class C = mp::identity>
    using at = typename detail::_unpack<mp::drop_front_c<i::value, mp::front<C>>, L>::type;

    template<class L, unsigned i, class C = mp::identity>
    using at_c = typename detail::_unpack<mp::drop_front_c<i, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at0 = typename detail::_unpack<mp::front<C>, L>::type;

    template<class L, class C = mp::identity>
    using at1 = typename detail::_unpack<mp::drop_front_c<1, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at2 = typename detail::_unpack<mp::drop_front_c<2, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at3 = typename detail::_unpack<mp::drop_front_c<3, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at4 = typename detail::_unpack<mp::drop_front_c<4, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at5 = typename detail::_unpack<mp::drop_front_c<5, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at6 = typename detail::_unpack<mp::drop_front_c<6, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at7 = typename detail::_unpack<mp::drop_front_c<7, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at8 = typename detail::_unpack<mp::drop_front_c<8, mp::front<C>>, L>::type;

    template<class L, class C = mp::identity>
    using at9 = typename detail::_unpack<mp::drop_front_c<9, mp::front<C>>, L>::type;
  }
}
