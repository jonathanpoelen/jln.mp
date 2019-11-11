#pragma once

#include "../list/list.hpp"
#include "fold_left.hpp"
#include "../functional/call.hpp"

namespace jln::mp
{
  namespace detail
  {
    template<class seqs, class seq>
    struct _cartesian;

    template<class, class>
    struct _product;
  }

  // product.hpp
  template<class F = listify, class C = listify>
  struct product
  {
    // TODO
  //   template<class, class>
  //   struct _product;
  //
  // public:
    template<class seq1, class seq2>
    using f = typename detail::_product<seq1, seq2>
      ::template f<F, C>::type;
  };

  template<class C = listify>
  struct cartesian
  {
    // TODO
  //   template<class, class>
  //   struct _cartesian;
  //
  // public:
    template<class... seqs>
    using f = call<fold_left<mp::cfl<detail::_cartesian>, unpack<C>>,
      list<list<>>, seqs...>;
  };
}

namespace jln::mp::detail
{
    template<class, class>
    struct _product;

    // TODO dispatch<C, partial<F, xs...>, ys...> ?
    template<
      template<class...> class Lx, class... xs,
      template<class...> class Ly, class... ys>
    struct _product<Lx<xs...>, Ly<ys...>>
    {
      template<class F, class C, class = void>
      struct f
      {
        using type = typename C::template f<
          typename F::template f<xs..., ys>...>;
      };

      template<class C, class _>
      struct f<listify, C, _>
      {
        using type = typename C::template f<list<xs..., ys>...>;
      };

      template<class F, class _>
      struct f<F, listify, _>
      {
        using type = list<typename F::template f<xs..., ys>...>;
      };

      template<class _>
      struct f<listify, listify, _>
      {
        using type = list<list<xs..., ys>...>;
      };
    };

    template<class... seqs, class L>
    struct _cartesian<list<seqs...>, L>
    {
      using type = list<
        typename _product<seqs, L>::template f<listify, listify>...>;
    };
}
