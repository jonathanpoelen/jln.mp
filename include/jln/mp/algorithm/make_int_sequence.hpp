#pragma once

#include <jln/mp/list/listify.hpp>
#include <jln/mp/number/numbers.hpp>

#include <utility>


#if defined(__has_builtin)
#  if __has_builtin(__make_integer_seq)
#    define JLN_MP_USE_INTEGER_PACK 0
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#  elif __has_builtin(__integer_pack)
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#elif defined(_MSC_VER)
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 1
#elif defined(__GNUC__)
#  if __GNUC__ >= 8
#    define JLN_MP_USE_INTEGER_PACK 1
#    define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#  endif
#endif

#ifndef JLN_MP_USE_INTEGER_PACK
#  define JLN_MP_USE_INTEGER_PACK 0
#  define JLN_MP_USE_MAKE_INTEGER_SEQ 0
#endif


namespace jln::mp
{
  /// \cond
  namespace detail
  {
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    template<std::size_t>
#else
    template<class>
#endif
    struct _make_int_sequence;
  }
  /// \endcond


  /// \ingroup number

  /// Generates an incremental sequence of \c n \c int_.
  /// \treturn \sequence
  /// \see make_int_sequence, iota
  template<class C = numbers<>>
  struct make_int_sequence_v
  {
    template<class n>
#if JLN_MP_USE_MAKE_INTEGER_SEQ || JLN_MP_USE_INTEGER_PACK
    using f = typename detail::_make_int_sequence<n::value>
      ::type::template f<C>;
#else
    using f = typename detail::_make_int_sequence<
      std::make_index_sequence<n::value>>::template f<C>;
#endif
  };

  template<class C = mp::listify>
  using make_int_sequence = make_int_sequence_v<mp::numbers<C>>;

  namespace emp
  {
    template<class n, class C = mp::numbers<>>
    using make_int_sequence_v = typename mp::make_int_sequence_v<C>::template f<n>;

    template<int_ n, class C = mp::numbers<>>
    using make_int_sequence_v_c = make_int_sequence_v<mp::number<n>, C>;

    template<class n, class C = mp::listify>
    using make_int_sequence = typename mp::make_int_sequence<C>::template f<n>;

    template<int_ n, class C = mp::listify>
    using make_int_sequence_c = make_int_sequence<mp::number<n>, C>;
  }
} // namespace jln::mp


/// \cond
namespace jln::mp::detail
{
#if JLN_MP_USE_MAKE_INTEGER_SEQ
  template<class, int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename C::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = __make_integer_seq<_make_int_sequence_impl, int_, n>;
  };
#elif JLN_MP_USE_INTEGER_PACK
  template<int_... ns>
  struct _make_int_sequence_impl
  {
    template<class C>
    using f = typename JLN_MP_TRACE_F(C)::template f<ns...>;
  };

  template<std::size_t n>
  struct _make_int_sequence
  {
    using type = _make_int_sequence_impl<__integer_pack(n)...>;
  };
#else
  template<std::size_t... ns>
  struct _make_int_sequence<std::integer_sequence<std::size_t, ns...>>
  {
    template<class C>
    using f = typename JLN_MP_TRACE_F(C)::template f<int_(ns)...>;
  };
#endif
}
/// \endcond

#undef JLN_MP_USE_INTEGER_PACK
#undef JLN_MP_USE_MAKE_INTEGER_SEQ

#if 0
namespace jln::mp::emp
{
  template<int_ n, class C = listify>
  using make_int_sequence_c = typename _make_int_sequence<
    (n == 0 ? 0 : n == 1 ? -1 : n-1)
  >::template f<jln::mp::numbers<C>>;
}

namespace jln::mp::detail
{
  template<int_...>
  class enumeration;

  template<bool, int_ n, class ns>
  struct _make_int_sequence_impl;

  template<int_ n, int_... ns>
  struct _make_int_sequence_impl<false, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)...>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)...>;
  };

  template<int_ n, int_... ns>
  struct _make_int_sequence_impl<true, n, enumeration<ns...>>
  {
    using type = enumeration<ns..., (n+ns)..., n*2+1>;

    template<class C>
    using f = typename C::template f<0, ns..., (n+ns)..., n*2+1>;
  };

  template<int_ n>
  struct _make_int_sequence
 : _make_int_sequence_impl<bool(n & 1), n/2, typename _make_int_sequence<n / 2>::type>
  {};

  template<>
  struct _make_int_sequence<0>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<>;
  };

  template<>
  struct _make_int_sequence<-1>
  {
    using type = enumeration<>;

    template<class C>
    using f = typename C::template f<0>;
  };
}
#endif
