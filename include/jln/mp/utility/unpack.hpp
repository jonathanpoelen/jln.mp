#pragma once

namespace jln::mp
{
  namespace detail
  {
    template <typename C, typename L, typename... Ts>
    struct _unpack;
  }

  template<class C>
  struct unpack
  {
    template<class... Ls>
    using f = typename detail::_unpack<C, Ls...>::type;
  };
} // namespace jln::mp

namespace jln::mp::detail
{
  template<class C, template<class...> class Seq, class... Ts, class... xs>
  struct _unpack<C, Seq<Ts...>, xs...>
  {
      using type = typename C::template f<xs..., Ts...>;
  };
}
