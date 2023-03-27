#include "test/test_context.hpp"
#include "test/test_case.hpp"

#include "jln/mp/smp/optimizer/types.hpp"
#include "jln/mp/functional/lift.hpp"

TEST_SUITE_BEGIN()

template<class... xs>
using U = mp::optimizer::types::basic_union<xs...>;

template<class... xs>
using S = mp::optimizer::types::basic_seq<xs...>;

template<class... xs>
using L = mp::optimizer::types::basic_list<xs...>;

template<class x>
using P = mp::optimizer::types::basic_pack<x>;

using n = mp::optimizer::types::number;
using b = mp::optimizer::types::boolean;

TEST()
{
  namespace mp = jln::mp;
  using namespace jln::mp::optimizer::types;

  test_context<mp::lift<mp::optimizer::list_t>, void>()
    .test<mp::list<>>()
    .test<mp::list<int>, int>()
    .test<mp::list<int>, S<int>>()
    .test<mp::list<int, long>, S<int>, S<long>>()
    .test<L<U<int, long>>, U<int, long>>()
    .test<L<int, n>, S<int, n>>()
    .test<L<n>, n>()
    .test<L<n, n>, n, n>()
    .test<L<n, n>, S<n, n>>()
    .test<L<n, b, na>, n, b, na, S<>>()
    .test<L<n, b, na, void, n, int>, n, b, na, S<void, n>, int>()
    .test<L<n, b, U<void, n>>, n, b, U<void, n>>()
    .test<L<P<n>>, P<n>>()
    .test<L<P<n>, b, n, n, P<n>>, P<n>, P<n>, b, n, P<n>, n, P<n>>()
    .test<U<uncallable, L<n, b, void, n>>, n, b, U<uncallable, S<void, n>>>()
    .test<U<uncallable, L<n, b, U<void, n>>>, n, b, U<uncallable, void, n>>()
    .test<uncallable, n, b, uncallable, S<void, n>, n>()
    ;

  test_context<mp::lift<mp::optimizer::seq>, void>()
    .test<S<>>()
    .test<n, n>()
    .test<S<n, n>, n, n>()
    .test<S<n, n>, S<n, n>>()
    .test<S<n, b, na>, n, b, na, S<>>()
    .test<S<n, b, na, void, n, int>, n, b, na, S<void, n>, int>()
    .test<any, any>()
    .test<S<any, any>, any, any>()
    .test<S<any, P<any>>, P<any>, any>()
    .test<S<any, P<any>>, any, P<any>>()
    .test<P<any>, P<any>, P<any>>()
    .test<S<n, b, U<void, n>>, n, b, U<void, n>>()
    .test<S<P<n>, b, n, n, P<n>>, P<n>, P<n>, b, n, P<n>, n, P<n>>()
    .test<U<uncallable, S<n, b, void, n>>, n, b, U<uncallable, S<void, n>>>()
    .test<U<uncallable, S<n, b, U<void, n>>>, n, b, U<uncallable, void, n>>()
    .test<uncallable, n, b, uncallable, S<void, n>, n>()
    ;

  test_context<mp::lift<mp::optimizer::pack>, void>()
    .test<P<n>, P<n>>()
    .test<P<n>, n>()
    .test<S<>, S<>>()
    .test<P<S<n, b>>, P<S<n, b>>>()
    .test<U<P<void>, P<n>>, U<void, n>>()
    .test<P<n>, U<P<b>, n>>()
    .test<P<n>, U<n, S<>>>()
    .test<P<L<any>>, L<any>>()
    .test<uncallable, uncallable>()
    .test<U<uncallable, S<>>, U<uncallable, S<>>>()
    .test<U<uncallable, P<n>>, U<uncallable, n>>()
    .test<U<uncallable, P<n>>, U<uncallable, S<>, n>>()
    .test<U<uncallable, P<n>>, U<uncallable, n, b>>()
    .test<U<uncallable, P<n>>, U<uncallable, S<>, n, b, S<>>>()
    ;

  test_context<mp::lift<mp::optimizer::union_>, void>()
    .test<S<>>()
    .test<n, n>()
    .test<S<n, b>, S<n, b>>()
    .test<U<n, S<>>, U<n, S<>>>()
    .test<U<void, S<>>, U<void, S<>>, U<void, S<>>>()
    .test<U<S<>, void>, U<S<>, void>, U<void, S<>>>()
    .test<U<n, S<>>, U<n, S<>>, U<n, S<>>>()
    .test<U<n, S<>>, U<S<>, n>, U<n, S<>>>()
    .test<n, n, b>()
    .test<n, n, b, n>()
    .test<b, mp::true_, mp::false_>()
    .test<b, mp::true_, b>()
    .test<b, mp::false_, b>()
    .test<n, mp::false_, b, n>()
    .test<n, mp::false_, n>()
    .test<n, mp::false_, mp::number<2>, n>()
    .test<U<mp::false_, mp::number<2>>, mp::false_, mp::number<2>>()
    .test<any, n, b, any>()
    .test<any, n, b, any, int>()
    .test<U<any, S<>>, n, b, S<>, any>()
    .test<U<any, S<b, n>>, n, b, S<b, n>, any>()
    .test<P<any>, n, b, P<any>>()
    .test<P<any>, n, b, P<any>, any>()
    .test<P<any>, n, b, P<any>, any, S<>>()
    .test<P<n>, n, P<n>>()
    .test<P<n>, P<n>, n>()
    .test<P<n>, P<n>, n, b>()
    .test<P<n>, U<P<b>, P<n>>, U<n, b>>()
    .test<U<P<n>, void>, U<P<b>, P<n>>, U<n, b>, void>()
    .test<U<P<b>, n, void>, P<b>, U<n, b>, void>()
    .test<U<P<mp::false_>, P<mp::true_>, b, void>, P<mp::true_>, P<mp::false_>, b, void>()
    .test<U<P<b>, void>, P<b>, mp::true_, mp::false_, void>()
    .test<uncallable, uncallable>()
    .test<U<uncallable, n>, n, uncallable>()
    .test<U<uncallable, n>, U<uncallable, n>>()
    .test<U<uncallable, n>, U<uncallable, n>, U<uncallable, n>>()
    .test<U<uncallable, n>, U<uncallable, n>, U<uncallable, b>>()
    .test<U<uncallable, n>, U<uncallable, n>, U<uncallable, b, n>>()
    ;
}

TEST_SUITE_END()
