#pragma once

// TODO within unpack.hpp
namespace jln::mp
{
  namespace detail
  {
    template <typename C, typename L, typename... Ts>
    struct _unpack_append;
  }

  // TODO rename to reverse_unpack ?
  template<class C>
  struct unpack_append
  {
    template<class... Ls>
    // TODO _unpack_append<Ls...>::template f<C> ?
    using f = typename detail::_unpack_append<C, Ls...>::type;
  };
} // namespace jln::mp

namespace jln::mp::detail
{
  template<class C, template<class...> class Seq, class... Ts, class... xs>
  struct _unpack_append<C, Seq<Ts...>, xs...>
  {
      using type = typename C::template f<Ts..., xs...>;
  };
}
