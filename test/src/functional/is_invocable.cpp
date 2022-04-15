#include "test/test_context.hpp"
#include "test/test_case.hpp"

#include "jln/mp/functional/is_invocable.hpp"

TEST_SUITE_BEGIN()

JLN_MP_DIAGNOSTIC_PUSH()
JLN_MP_DIAGNOSTIC_CLANG_IGNORE("-Wunused-const-variable")
struct A;
struct B { template<class> using f = int; };
struct C { template<int> using f = int; };
struct D { template<class x> using f = typename x::type; };
struct E { template<class x> static constexpr int f = x::value; };
struct F { template<class...> using f = int; };
struct G { template<class...> static constexpr int f = 1; };
struct H { template<int...> using f = int; };
struct I { template<int...> static constexpr int f = 1; };

struct t { using type = int; };
struct v { static constexpr int value = 1; };
JLN_MP_DIAGNOSTIC_POP()

template<class... xs, class a, class b, class c, class d, class e, class f, class g, class h, class i>
void invoke(a, b, c, d, e, f, g, h, i)
{
  using jln::mp::is_invocable;

  a{} = is_invocable<A>::f<xs...>{};
  b{} = is_invocable<B>::f<xs...>{};
  c{} = is_invocable<C>::f<xs...>{};
  d{} = is_invocable<D>::f<xs...>{};
  e{} = is_invocable<E>::f<xs...>{};
  f{} = is_invocable<F>::f<xs...>{};
  g{} = is_invocable<G>::f<xs...>{};
  h{} = is_invocable<H>::f<xs...>{};
  i{} = is_invocable<I>::f<xs...>{};
}

TEST()
{
  using namespace jln::mp;

  test_mulary_pack<is_invocable>();
  test_mulary_pack<is_invocable, identity>();

  auto y = true_{};
  auto n = false_{};

  //          A  B  C  D  E  F  G  H  I
  invoke<   >(n, n, n, n, n, y, n, y, n);
  invoke<int>(n, y, n, n, n, y, n, n, n);
  invoke<t  >(n, y, n, y, n, y, n, n, n);
  invoke<v  >(n, y, n, n, n, y, n, n, n);
}

TEST_SUITE_END()
