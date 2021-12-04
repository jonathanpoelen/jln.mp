#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/utility/unpack.hpp>


namespace jln::mp
{
  /// \ingroup algorithm

  /// Executes \c F on every element of a \sequence.
  /// \treturn \sequence
#if defined(JLN_MP_DOXYGENATING) || JLN_MP_MSVC
  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = JLN_MP_DCALL_TRACE_XS(xs, C, JLN_MP_DCALL_TRACE_XS(xs, F, xs)...);
  };
#else
  /// \cond
  namespace detail
  {
    template<class C, class F, class...xs>
    using transform_impl = JLN_MP_DCALL_TRACE_XS(xs, C, typename F::template f<xs>...);
  }
  /// \endcond

  template<class F, class C = listify>
  struct transform
  {
    template<class... xs>
    using f = detail::transform_impl<C,
      typename conditional_c<sizeof...(xs) < JLN_MP_MAX_CALL_ELEMENT>
      ::template f<JLN_MP_TRACE_F(F), detail::too_many_arguments_error>,
      xs...
    >;
  };
#endif

  namespace emp
  {
    template<class L, class C = mp::listify>
    using transform = unpack<L, mp::transform<C>>;
  }
}


/// \cond
namespace jln::mp::detail
{
  template<class T>
  struct optimize_useless_transform_unpack
  {
    using type = T;
  };

  template<class T>
  using optimize_useless_transform_unpack_t
    = typename optimize_useless_transform_unpack<T>::type;

  template<class F>
  struct optimize_useless_transform_unpack_impl
  {
    template<class C>
    using f = transform<F, C>;
  };

  template<>
  struct optimize_useless_transform_unpack_impl<identity>
  {
    template<class C>
    using f = optimize_useless_transform_unpack_t<C>;
  };

  template<class F, class C>
  struct optimize_useless_transform_unpack<transform<F, C>>
  {
    using type = typename optimize_useless_transform_unpack_impl<optimize_useless_unpack_t<F>>
      ::template f<C>;
  };
}
/// \endcond
